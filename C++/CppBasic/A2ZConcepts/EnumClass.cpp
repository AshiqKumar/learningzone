
/***************************************************************************
 This code demonstrates how to use C++11 scoped enums (`enum class`) with a specified underlying type, safe value assignment,
and comparison. It also shows that scoped enums prevent implicit conversions and require explicit scoping for their values.
`enum class` in C++ is called a **scoped enumeration**. It was introduced in C++11 to provide better type safety and scoping compared to traditional enums.

Key features of `enum class`:
- Scoped: Enum values must be accessed with their scope (e.g., `RANK::FIRST`), preventing name clashes.
- Strongly typed: No implicit conversion to `int` or other types.
- Underlying type: You can specify the underlying type (e.g., `: short int`).

Key Differences from Traditional enum

| Feature            | enum                | enum class           |
|--------------------|---------------------|----------------------|
| Scope              | Unscoped            | Scoped               |
| Type Safety        | Weak                | Strong               |
| Implicit Conversion| Converts to int     | No implicit conversion|
| Usage              | Red                 | Color::Red           |

RANK obj = RANK::FIRST; // Correct
// RANK obj = FIRST;    // Error: must use scope

`enum class` makes enums safer and avoids accidental misuse or name conflicts.
***************************************************************************/
#include<iostream>
using namespace std;

int main()
{
	enum class RANK  : short int   //underlying type - if specified shall be integral types only.
	{
		FIRST,
		SECOND,
		THIRD
	};

	//RANK obj = FIRST; //it will give error: 'FIRST' was not declared in this scope
	RANK obj = RANK::FIRST; // Correct usage with scope
	RANK obj1 = RANK::FIRST;
	auto obj2 = RANK::SECOND;
	if (obj1 != obj2)
		cout << "not equal" << endl;
	else
		cout << "equal" << endl;
	
}