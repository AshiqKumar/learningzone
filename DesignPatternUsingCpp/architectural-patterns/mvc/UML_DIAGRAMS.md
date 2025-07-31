# MVC Architecture UML Diagrams

## Class Diagram

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           MVC ARCHITECTURE OVERVIEW                          │
└─────────────────────────────────────────────────────────────────────────────┘

┌─────────────────┐         ┌─────────────────┐         ┌─────────────────┐
│     MODEL       │         │      VIEW       │         │   CONTROLLER    │
│                 │         │                 │         │                 │
│  ┌───────────┐  │         │  ┌───────────┐  │         │  ┌───────────┐  │
│  │  Student  │  │         │  │StudentView│  │         │  │ Student   │  │
│  │           │  │         │  │           │  │         │  │Controller │  │
│  │ - id      │  │         │  │ + display │  │         │  │           │  │
│  │ - name    │  │         │  │ + input   │  │         │  │ + run()   │  │
│  │ - email   │  │         │  │ + show    │  │         │  │ + handle  │  │
│  │ - age     │  │         │  │ + notify  │  │         │  │   Actions │  │
│  │ - gpa     │  │         │  └───────────┘  │         │  └───────────┘  │
│  └───────────┘  │         │                 │         │                 │
│                 │         │                 │         │                 │
│  ┌───────────┐  │         │                 │         │                 │
│  │StudentModel│ │         │                 │         │                 │
│  │           │  │         │                 │         │                 │
│  │ + add()   │  │◄────────┤                 │         │                 │
│  │ + update()│  │ observes│                 │         │                 │
│  │ + remove()│  │         │                 │         │                 │
│  │ + find()  │  │         │                 │         │                 │
│  │ + notify()│  │         │                 │         │                 │
│  └───────────┘  │         │                 │         │                 │
└─────────────────┘         └─────────────────┘         └─────────────────┘
         ▲                           ▲                           │
         │                           │                           │
         │ manipulates               │ updates                   │
         │                           │                           │
         └───────────────────────────┼───────────────────────────┘
                                     │
                                     ▼ controls
```

## Detailed Class Relationships

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                          DETAILED CLASS DIAGRAM                              │
└─────────────────────────────────────────────────────────────────────────────┘

┌────────────────────┐
│    <<interface>>   │
│   ModelObserver    │
├────────────────────┤
│ + onStudentAdded() │
│ + onStudentUpdated()│
│ + onStudentRemoved()│
│ + onModelCleared() │
└────────────────────┘
           ▲
           │ implements
           │
┌────────────────────┐    ┌────────────────────┐    ┌────────────────────┐
│      Student       │    │    StudentView     │    │  StudentController │
├────────────────────┤    ├────────────────────┤    ├────────────────────┤
│ - id: int          │    │ + displayMenu()    │    │ - model: unique_ptr│
│ - name: string     │    │ + displayStudent() │    │ - view: unique_ptr │
│ - email: string    │    │ + getUserInput()   │    │ - isRunning: bool  │
│ - age: int         │    │ + showSuccess()    │    ├────────────────────┤
│ - gpa: double      │    │ + showError()      │    │ + run()            │
├────────────────────┤    │ + clearScreen()    │    │ + handleAddStudent()│
│ + getId()          │    │ + waitForInput()   │    │ + handleUpdate()   │
│ + getName()        │    ├────────────────────┤    │ + handleRemove()   │
│ + getEmail()       │    │ + onStudentAdded() │    │ + handleSearch()   │
│ + getAge()         │    │ + onStudentUpdated()│   │ + validateInput()  │
│ + getGpa()         │    │ + onStudentRemoved()│   └────────────────────┘
│ + setters...       │    │ + onModelCleared() │              │
│ + toString()       │    └────────────────────┘              │
│ + isValid()        │                                        │
└────────────────────┘                                        │
           │                                                  │
           │ contains                                         │
           ▼                                                  │
┌────────────────────┐                                       │
│   StudentModel     │◄──────────────────────────────────────┘
├────────────────────┤                uses
│ - students: vector │
│ - observers: vector│
│ - nextId: int      │
├────────────────────┤
│ + addStudent()     │
│ + updateStudent()  │
│ + removeStudent()  │
│ + findStudent()    │
│ + getAllStudents() │
│ + searchByName()   │
│ + getStatistics()  │
│ + addObserver()    │
│ + removeObserver() │
│ + notify...()      │
└────────────────────┘
```

## Sequence Diagram: Add Student Flow

```
User    Controller    Model      View
 │          │          │          │
 │ 1. Menu  │          │          │
 │ Choice   │          │          │
 │────────► │          │          │
 │          │ 2. Get   │          │
 │          │ Input    │          │
 │          │────────────────────► │
 │          │          │          │
 │          │ 3. Student Data     │
 │          │◄────────────────────│
 │          │          │          │
 │          │ 4. Add   │          │
 │          │ Student  │          │
 │          │────────► │          │
 │          │          │          │
 │          │          │ 5. Notify│
 │          │          │ Observer │
 │          │          │────────► │
 │          │          │          │
 │          │ 6. Success          │
 │          │ Message             │
 │          │────────────────────► │
 │          │          │          │
 │ 7. Display         │          │
 │ Confirmation       │          │
 │◄───────────────────────────────│
```

## State Diagram: Application Flow

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                            APPLICATION STATE FLOW                            │
└─────────────────────────────────────────────────────────────────────────────┘

              ┌─────────────┐
              │    Start    │
              └─────────────┘
                     │
                     ▼
              ┌─────────────┐
              │Initialize   │
              │MVC Components│
              └─────────────┘
                     │
                     ▼
              ┌─────────────┐
         ┌────│Display Menu │◄─────┐
         │    └─────────────┘      │
         │           │             │
         ▼           ▼             │
    ┌─────────┐ ┌─────────┐        │
    │   Add   │ │  View   │        │
    │ Student │ │Students │        │
    └─────────┘ └─────────┘        │
         │           │             │
         │           ▼             │
         │    ┌─────────┐          │
         │    │ Search  │          │
         │    │Students │          │
         │    └─────────┘          │
         │           │             │
         │           ▼             │
         │    ┌─────────┐          │
         │    │ Update  │          │
         │    │ Student │          │
         │    └─────────┘          │
         │           │             │
         │           ▼             │
         │    ┌─────────┐          │
         │    │ Remove  │          │
         │    │ Student │          │
         │    └─────────┘          │
         │           │             │
         │           ▼             │
         │    ┌─────────┐          │
         │    │Statistics│         │
         │    └─────────┘          │
         │           │             │
         └───────────┼─────────────┘
                     │
                     ▼
              ┌─────────────┐
              │    Exit?    │
              └─────────────┘
                     │ Yes
                     ▼
              ┌─────────────┐
              │   Cleanup   │
              └─────────────┘
                     │
                     ▼
              ┌─────────────┐
              │     End     │
              └─────────────┘
```

## Component Interaction Diagram

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                        COMPONENT INTERACTIONS                                │
└─────────────────────────────────────────────────────────────────────────────┘

                    ┌─────────────────┐
                    │      USER       │
                    └─────────────────┘
                             │
                             │ Input/Actions
                             ▼
    ┌─────────────────────────────────────────────────────────┐
    │                    VIEW LAYER                           │
    │  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐     │
    │  │   Display   │  │    Input    │  │  Feedback   │     │
    │  │  Functions  │  │ Collection  │  │ & Messages  │     │
    │  └─────────────┘  └─────────────┘  └─────────────┘     │
    └─────────────────────────────────────────────────────────┘
                             │                  ▲
                             │ User Events      │ UI Updates
                             ▼                  │
    ┌─────────────────────────────────────────────────────────┐
    │                 CONTROLLER LAYER                        │
    │  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐     │
    │  │   Action    │  │ Validation  │  │   Flow      │     │
    │  │  Handlers   │  │  & Logic    │  │  Control    │     │
    │  └─────────────┘  └─────────────┘  └─────────────┘     │
    └─────────────────────────────────────────────────────────┘
                             │                  ▲
                             │ Data Operations  │ State Changes
                             ▼                  │
    ┌─────────────────────────────────────────────────────────┐
    │                    MODEL LAYER                          │
    │  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐     │
    │  │   Student   │  │ Business    │  │ Observer    │     │
    │  │    Data     │  │   Logic     │  │ Management  │     │
    │  └─────────────┘  └─────────────┘  └─────────────┘     │
    └─────────────────────────────────────────────────────────┘
                             │
                             │ Persistence (Future)
                             ▼
                    ┌─────────────────┐
                    │   DATA STORE    │
                    │ (File/Database) │
                    └─────────────────┘
```

---

*These diagrams illustrate the clean separation of concerns and the flow of data and control through the MVC architecture.*
