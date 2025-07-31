# Real-time Processing Theory - Algorithms and Systems

## ⚡ Real-time Systems Fundamentals

### 1. Real-time Processing Concepts

#### 1.1 Temporal Constraints

**Types of Real-time Systems**:
- **Hard Real-time**: Missing deadline causes system failure
  - Example: Automotive brake systems, medical devices
- **Soft Real-time**: Missing deadline degrades performance
  - Example: Video streaming, interactive games
- **Firm Real-time**: Late results are useless but not catastrophic
  - Example: Financial trading systems

**Timing Terminology**:
```
Release time: When task becomes available
Deadline: Latest acceptable completion time
Response time: Time from release to completion
Period: Time between successive releases (for periodic tasks)
Utilization: Fraction of CPU time required (U = C/T)

Where:
- C = Computation time
- T = Period
```

#### 1.2 Scheduling Theory

**Rate Monotonic Scheduling (RMS)**:
- Optimal for fixed-priority preemptive scheduling
- Higher frequency tasks get higher priority
- Schedulable if: U = Σ(Cᵢ/Tᵢ) ≤ n(2^(1/n) - 1)

**Earliest Deadline First (EDF)**:
- Optimal for dynamic priority scheduling  
- Task with earliest deadline gets highest priority
- Schedulable if: U = Σ(Cᵢ/Tᵢ) ≤ 1

### 2. Video Processing Pipeline Theory

#### 2.1 Frame Rate Mathematics

**Frame Rate Relationships**:
```
Frame Rate (fps) = 1 / Frame Period (seconds)
Processing Time ≤ Frame Period for real-time

Example:
30 fps → 33.33 ms per frame
60 fps → 16.67 ms per frame
120 fps → 8.33 ms per frame
```

**Processing Budget**:
```
Total Processing Time = Acquisition + Processing + Display
Acquisition Time: Camera sensor readout time
Processing Time: Algorithm execution time
Display Time: Rendering and output time

For 30 fps (33.33 ms total):
- Acquisition: ~1-5 ms
- Processing: ~25-30 ms available
- Display: ~2-5 ms
```

#### 2.2 Pipeline Parallelism

**Multi-stage Pipeline**:
```
Stage 1: Frame Acquisition
Stage 2: Preprocessing (resize, normalize)
Stage 3: Feature Extraction
Stage 4: ML Inference
Stage 5: Post-processing
Stage 6: Display/Output
```

**Pipeline Throughput**:
```
Throughput = 1 / max(Stage_Time_i)
Latency = Σ Stage_Time_i

Pipeline Efficiency = Throughput × Latency / Number_of_Stages
```

### 3. Multi-threading Patterns

#### 3.1 Producer-Consumer Pattern

**Mathematical Model**:
```cpp
// Buffer capacity: N
// Producer rate: λ (frames/second)
// Consumer rate: μ (frames/second)

// Queue stability condition: μ > λ
// Average queue length: ρ/(1-ρ) where ρ = λ/μ
// Average waiting time: (ρ/μ)/(1-ρ)
```

**Implementation Pattern**:
```cpp
class FrameBuffer {
private:
    std::queue<Frame> buffer;
    std::mutex buffer_mutex;
    std::condition_variable not_empty;
    std::condition_variable not_full;
    size_t max_size;

public:
    void produce(const Frame& frame) {
        std::unique_lock<std::mutex> lock(buffer_mutex);
        
        // Wait if buffer is full
        not_full.wait(lock, [this] { return buffer.size() < max_size; });
        
        buffer.push(frame);
        lock.unlock();
        not_empty.notify_one();
    }
    
    Frame consume() {
        std::unique_lock<std::mutex> lock(buffer_mutex);
        
        // Wait if buffer is empty
        not_empty.wait(lock, [this] { return !buffer.empty(); });
        
        Frame frame = buffer.front();
        buffer.pop();
        lock.unlock();
        not_full.notify_one();
        
        return frame;
    }
};
```

#### 3.2 Thread Pool Pattern

**Work Distribution**:
```cpp
class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;

public:
    ThreadPool(size_t threads) : stop(false) {
        for(size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while(true) {
                    std::function<void()> task;
                    
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this] {
                            return stop || !tasks.empty();
                        });
                        
                        if(stop && tasks.empty()) return;
                        
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    
                    task();
                }
            });
        }
    }
    
    template<class F>
    auto enqueue(F&& f) -> std::future<typename std::result_of<F()>::type> {
        using return_type = typename std::result_of<F()>::type;
        
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::forward<F>(f)
        );
        
        std::future<return_type> res = task->get_future();
        
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if(stop) throw std::runtime_error("enqueue on stopped ThreadPool");
            
            tasks.emplace([task](){ (*task)(); });
        }
        
        condition.notify_one();
        return res;
    }
};
```

### 4. Lock-free Data Structures

#### 4.1 Lock-free Queue

**Single Producer, Single Consumer (SPSC)**:
```cpp
template<typename T>
class LockFreeQueue {
private:
    struct Node {
        std::atomic<T*> data;
        std::atomic<Node*> next;
        
        Node() : data(nullptr), next(nullptr) {}
    };
    
    std::atomic<Node*> head;
    std::atomic<Node*> tail;
    
public:
    LockFreeQueue() {
        Node* dummy = new Node;
        head.store(dummy);
        tail.store(dummy);
    }
    
    void enqueue(T item) {
        Node* new_node = new Node;
        T* data = new T(std::move(item));
        new_node->data.store(data);
        
        Node* prev_tail = tail.exchange(new_node);
        prev_tail->next.store(new_node);
    }
    
    bool dequeue(T& result) {
        Node* head_node = head.load();
        Node* next = head_node->next.load();
        
        if (next == nullptr) {
            return false;  // Queue is empty
        }
        
        T* data = next->data.load();
        if (data == nullptr) {
            return false;
        }
        
        result = *data;
        delete data;
        head.store(next);
        delete head_node;
        
        return true;
    }
};
```

#### 4.2 Memory Ordering Considerations

**Memory Ordering Types**:
```cpp
// Relaxed: No synchronization constraints
std::atomic<int> counter;
counter.store(42, std::memory_order_relaxed);

// Acquire-Release: Synchronizes with other acquire/release operations
std::atomic<bool> ready;
ready.store(true, std::memory_order_release);  // Publisher
if (ready.load(std::memory_order_acquire)) {   // Subscriber
    // All previous writes by publisher are visible
}

// Sequential Consistency: Global order of all atomic operations
counter.store(42, std::memory_order_seq_cst);  // Default
```

### 5. Cache Optimization Theory

#### 5.1 Cache Performance Models

**Cache Hit/Miss Analysis**:
```
Cache Hit Rate: H = Number of hits / Total memory accesses
Cache Miss Rate: M = 1 - H

Average Memory Access Time (AMAT):
AMAT = Hit_Time + Miss_Rate × Miss_Penalty

Multi-level Cache:
AMAT = Hit_Time_L1 + Miss_Rate_L1 × (Hit_Time_L2 + Miss_Rate_L2 × Miss_Penalty_L2)
```

**Working Set Theory**:
```
Working Set W(t,τ): Set of pages referenced in time interval [t-τ, t]
Temporal Locality: References cluster in time
Spatial Locality: References cluster in space

For image processing:
- Temporal: Successive frames have similar content
- Spatial: Neighboring pixels are often processed together
```

#### 5.2 Cache-Friendly Algorithms

**Loop Tiling/Blocking**:
```cpp
// Original: Poor cache behavior
for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            C[i][j] += A[i][k] * B[k][j];  // B accessed non-sequentially
        }
    }
}

// Tiled: Better cache utilization
const int TILE_SIZE = 64;  // Fit in cache
for (int ii = 0; ii < N; ii += TILE_SIZE) {
    for (int jj = 0; jj < N; jj += TILE_SIZE) {
        for (int kk = 0; kk < N; kk += TILE_SIZE) {
            // Process tile
            for (int i = ii; i < min(ii+TILE_SIZE, N); i++) {
                for (int j = jj; j < min(jj+TILE_SIZE, N); j++) {
                    for (int k = kk; k < min(kk+TILE_SIZE, N); k++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
    }
}
```

### 6. Memory Management Strategies

#### 6.1 Object Pooling

**Memory Pool Implementation**:
```cpp
template<typename T>
class ObjectPool {
private:
    std::queue<std::unique_ptr<T>> objects;
    std::mutex pool_mutex;
    std::function<std::unique_ptr<T>()> factory;
    
public:
    ObjectPool(std::function<std::unique_ptr<T>()> f, size_t initial_size = 10)
        : factory(f) {
        for (size_t i = 0; i < initial_size; ++i) {
            objects.push(factory());
        }
    }
    
    std::unique_ptr<T> acquire() {
        std::lock_guard<std::mutex> lock(pool_mutex);
        if (objects.empty()) {
            return factory();  // Create new if pool empty
        } else {
            auto obj = std::move(objects.front());
            objects.pop();
            return obj;
        }
    }
    
    void release(std::unique_ptr<T> obj) {
        std::lock_guard<std::mutex> lock(pool_mutex);
        objects.push(std::move(obj));
    }
};

// Usage for frame buffers
ObjectPool<FrameBuffer> frame_pool([]() {
    return std::make_unique<FrameBuffer>(1920, 1080);
}, 10);  // Pre-allocate 10 buffers
```

#### 6.2 Memory-Mapped Files

**Large Dataset Processing**:
```cpp
class MemoryMappedFile {
private:
    void* mapped_memory;
    size_t file_size;
    int fd;
    
public:
    MemoryMappedFile(const std::string& filename) {
        fd = open(filename.c_str(), O_RDONLY);
        struct stat sb;
        fstat(fd, &sb);
        file_size = sb.st_size;
        
        mapped_memory = mmap(nullptr, file_size, PROT_READ, 
                           MAP_PRIVATE, fd, 0);
        
        // Advise kernel about access pattern
        madvise(mapped_memory, file_size, MADV_SEQUENTIAL);
    }
    
    ~MemoryMappedFile() {
        munmap(mapped_memory, file_size);
        close(fd);
    }
    
    const uint8_t* data() const { return static_cast<const uint8_t*>(mapped_memory); }
    size_t size() const { return file_size; }
};
```

### 7. Real-time Scheduling Algorithms

#### 7.1 Priority Inversion Prevention

**Priority Inheritance Protocol**:
```cpp
class PriorityInheritanceMutex {
private:
    std::mutex internal_mutex;
    std::atomic<int> owner_priority;
    std::atomic<std::thread::id> owner_id;
    
public:
    void lock(int thread_priority) {
        std::thread::id current_thread = std::this_thread::get_id();
        
        // If mutex is held by lower priority thread, inherit priority
        if (owner_id.load() != std::thread::id{}) {
            int current_owner_priority = owner_priority.load();
            if (thread_priority > current_owner_priority) {
                // Boost owner's priority
                boost_thread_priority(owner_id.load(), thread_priority);
                owner_priority.store(thread_priority);
            }
        }
        
        internal_mutex.lock();
        owner_id.store(current_thread);
        owner_priority.store(thread_priority);
    }
    
    void unlock(int original_priority) {
        owner_id.store(std::thread::id{});
        owner_priority.store(0);
        
        // Restore original priority
        restore_thread_priority(std::this_thread::get_id(), original_priority);
        
        internal_mutex.unlock();
    }
};
```

#### 7.2 Deadline Scheduling

**Earliest Deadline First (EDF) Scheduler**:
```cpp
struct Task {
    std::function<void()> work;
    std::chrono::steady_clock::time_point deadline;
    int priority;
    
    bool operator<(const Task& other) const {
        return deadline > other.deadline;  // Min-heap based on deadline
    }
};

class EDFScheduler {
private:
    std::priority_queue<Task> task_queue;
    std::mutex queue_mutex;
    std::condition_variable queue_condition;
    std::vector<std::thread> workers;
    std::atomic<bool> shutdown;
    
    void worker_thread() {
        while (!shutdown.load()) {
            Task task;
            
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                queue_condition.wait(lock, [this] {
                    return !task_queue.empty() || shutdown.load();
                });
                
                if (shutdown.load()) break;
                
                task = task_queue.top();
                task_queue.pop();
            }
            
            // Check if deadline is still feasible
            auto now = std::chrono::steady_clock::now();
            if (now <= task.deadline) {
                task.work();
            } else {
                // Log deadline miss
                std::cout << "Deadline missed by " 
                         << std::chrono::duration_cast<std::chrono::milliseconds>
                            (now - task.deadline).count() << " ms" << std::endl;
            }
        }
    }
    
public:
    EDFScheduler(int num_workers) : shutdown(false) {
        for (int i = 0; i < num_workers; ++i) {
            workers.emplace_back(&EDFScheduler::worker_thread, this);
        }
    }
    
    void schedule_task(std::function<void()> work, 
                      std::chrono::milliseconds relative_deadline) {
        Task task{
            work,
            std::chrono::steady_clock::now() + relative_deadline,
            0
        };
        
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            task_queue.push(task);
        }
        queue_condition.notify_one();
    }
};
```

### 8. Quality of Service (QoS) Control

#### 8.1 Adaptive Quality Control

**Quality Metrics**:
```cpp
struct QualityMetrics {
    float frame_rate;           // Current FPS
    float processing_latency;   // End-to-end delay
    float cpu_utilization;      // CPU usage percentage
    float memory_usage;         // Memory usage percentage
    float accuracy;            // Algorithm accuracy (if measurable)
    
    float quality_score() const {
        // Weighted combination of metrics
        return 0.3f * (frame_rate / target_fps) +
               0.2f * (1.0f - processing_latency / max_latency) +
               0.2f * (1.0f - cpu_utilization) +
               0.1f * (1.0f - memory_usage) +
               0.2f * accuracy;
    }
};

class AdaptiveQualityController {
private:
    QualityMetrics current_metrics;
    float target_quality = 0.8f;
    
    struct QualityLevel {
        int resolution_scale;    // 1 = full, 2 = half, etc.
        int algorithm_complexity; // 0 = simple, 1 = medium, 2 = complex
        float quality_threshold;
    };
    
    std::vector<QualityLevel> quality_levels = {
        {4, 0, 0.3f},  // Low quality
        {2, 1, 0.6f},  // Medium quality  
        {1, 2, 1.0f}   // High quality
    };
    
    int current_level = 2;  // Start with high quality
    
public:
    void update_metrics(const QualityMetrics& metrics) {
        current_metrics = metrics;
        
        float current_quality = metrics.quality_score();
        
        // Adapt quality level
        if (current_quality < target_quality && current_level > 0) {
            current_level--;  // Reduce quality
            std::cout << "Reducing quality to level " << current_level << std::endl;
        } else if (current_quality > target_quality + 0.1f && 
                  current_level < quality_levels.size() - 1) {
            current_level++;  // Increase quality
            std::cout << "Increasing quality to level " << current_level << std::endl;
        }
    }
    
    QualityLevel get_current_quality() const {
        return quality_levels[current_level];
    }
};
```

#### 8.2 Frame Dropping Strategies

**Smart Frame Dropping**:
```cpp
class FrameDropper {
private:
    std::chrono::steady_clock::time_point last_process_time;
    std::chrono::milliseconds target_frame_interval;
    float drop_probability = 0.0f;
    
    // Exponential moving average for processing time
    float avg_process_time = 0.0f;
    const float alpha = 0.1f;  // Smoothing factor
    
public:
    FrameDropper(int target_fps) 
        : target_frame_interval(1000 / target_fps) {}
    
    bool should_process_frame() {
        auto now = std::chrono::steady_clock::now();
        auto time_since_last = std::chrono::duration_cast<std::chrono::milliseconds>
                              (now - last_process_time);
        
        // Update drop probability based on processing speed
        if (avg_process_time > target_frame_interval.count()) {
            drop_probability = std::min(0.9f, 
                (avg_process_time - target_frame_interval.count()) / 
                target_frame_interval.count());
        } else {
            drop_probability *= 0.9f;  // Decay drop probability
        }
        
        // Random dropping with calculated probability
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);
        
        if (dis(gen) < drop_probability) {
            return false;  // Drop this frame
        }
        
        last_process_time = now;
        return true;  // Process this frame
    }
    
    void update_processing_time(std::chrono::milliseconds process_time) {
        avg_process_time = alpha * process_time.count() + 
                          (1.0f - alpha) * avg_process_time;
    }
};
```

### 9. Performance Monitoring

#### 9.1 Real-time Profiling

**Performance Counter**:
```cpp
class PerformanceMonitor {
private:
    struct TimingInfo {
        std::chrono::steady_clock::time_point start;
        std::chrono::steady_clock::time_point end;
        std::string name;
    };
    
    thread_local static std::vector<TimingInfo> timing_stack;
    std::map<std::string, std::vector<float>> timing_history;
    std::mutex history_mutex;
    
public:
    class ScopedTimer {
    private:
        std::string name;
        std::chrono::steady_clock::time_point start_time;
        
    public:
        ScopedTimer(const std::string& timer_name) : name(timer_name) {
            start_time = std::chrono::steady_clock::now();
        }
        
        ~ScopedTimer() {
            auto end_time = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>
                           (end_time - start_time).count() / 1000.0f;
            
            PerformanceMonitor::instance().record_timing(name, duration);
        }
    };
    
    void record_timing(const std::string& name, float duration_ms) {
        std::lock_guard<std::mutex> lock(history_mutex);
        timing_history[name].push_back(duration_ms);
        
        // Keep only recent history
        if (timing_history[name].size() > 1000) {
            timing_history[name].erase(timing_history[name].begin());
        }
    }
    
    void print_statistics() {
        std::lock_guard<std::mutex> lock(history_mutex);
        
        for (const auto& [name, timings] : timing_history) {
            if (timings.empty()) continue;
            
            float sum = std::accumulate(timings.begin(), timings.end(), 0.0f);
            float avg = sum / timings.size();
            
            auto minmax = std::minmax_element(timings.begin(), timings.end());
            
            std::cout << name << ": avg=" << avg << "ms, min=" << *minmax.first 
                      << "ms, max=" << *minmax.second << "ms" << std::endl;
        }
    }
    
    static PerformanceMonitor& instance() {
        static PerformanceMonitor instance;
        return instance;
    }
};

#define PROFILE_SCOPE(name) PerformanceMonitor::ScopedTimer timer(name)
```

#### 9.2 System Resource Monitoring

**Resource Usage Tracker**:
```cpp
class ResourceMonitor {
private:
    std::atomic<bool> monitoring{true};
    std::thread monitor_thread;
    
    struct ResourceSnapshot {
        float cpu_usage;
        float memory_usage_mb;
        float gpu_usage;
        float gpu_memory_mb;
        std::chrono::steady_clock::time_point timestamp;
    };
    
    std::vector<ResourceSnapshot> history;
    std::mutex history_mutex;
    
    void monitor_resources() {
        while (monitoring.load()) {
            ResourceSnapshot snapshot;
            snapshot.timestamp = std::chrono::steady_clock::now();
            
            // Get CPU usage (platform-specific implementation needed)
            snapshot.cpu_usage = get_cpu_usage();
            
            // Get memory usage
            snapshot.memory_usage_mb = get_memory_usage_mb();
            
            // Get GPU usage (NVIDIA specific)
            #ifdef USE_CUDA
            snapshot.gpu_usage = get_gpu_usage();
            snapshot.gpu_memory_mb = get_gpu_memory_usage_mb();
            #endif
            
            {
                std::lock_guard<std::mutex> lock(history_mutex);
                history.push_back(snapshot);
                
                // Keep only recent history (last 60 seconds)
                auto cutoff = std::chrono::steady_clock::now() - std::chrono::seconds(60);
                history.erase(
                    std::remove_if(history.begin(), history.end(),
                        [cutoff](const ResourceSnapshot& s) {
                            return s.timestamp < cutoff;
                        }),
                    history.end());
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    
public:
    ResourceMonitor() : monitor_thread(&ResourceMonitor::monitor_resources, this) {}
    
    ~ResourceMonitor() {
        monitoring.store(false);
        if (monitor_thread.joinable()) {
            monitor_thread.join();
        }
    }
    
    ResourceSnapshot get_current_usage() {
        std::lock_guard<std::mutex> lock(history_mutex);
        return history.empty() ? ResourceSnapshot{} : history.back();
    }
    
    float get_average_cpu_usage(std::chrono::seconds duration) {
        auto cutoff = std::chrono::steady_clock::now() - duration;
        std::lock_guard<std::mutex> lock(history_mutex);
        
        float sum = 0.0f;
        int count = 0;
        
        for (const auto& snapshot : history) {
            if (snapshot.timestamp >= cutoff) {
                sum += snapshot.cpu_usage;
                count++;
            }
        }
        
        return count > 0 ? sum / count : 0.0f;
    }
};
```

---

This real-time processing theory provides the foundation for understanding timing constraints, scheduling, and performance optimization in the camera algorithms system.
