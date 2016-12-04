#pragma once
/*
Static math libary used to make maths calls 
*/
static class StaticMathsLib
{
public:
	StaticMathsLib();
	~StaticMathsLib();

	
	/*
	Clamps a var between a lower and upper vlaue

	@param	number		number wanint to clamp between 
	@param	lower		Lower number wanted to clamp agaist
	@param	upper		The highest number var should get to 
	*/
	template <typename T>
	static T Clamp(const T& number, const T& lower, const T& upper);
};

template<typename T>
inline T StaticMathsLib::Clamp(const T & number, const T & lower, const T & upper)
{

	return (number <= lower) ? lower : (number >= upper) ? upper : number;

}
