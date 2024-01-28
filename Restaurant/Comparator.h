#ifndef __COMPARATOR__H_
#define __COMPARATOR__H_

/**
Comparator Functor is used if a custom priority equation is needed
@return True if the first parameter is less than the second paramater
*/
template<typename T>
class Comparator {
	
	//Default comparator uses passed classes operators 
	virtual bool operator()(T Lhs, T Rhs) const ; 

}; // end Comparator


template<typename T>
bool Comparator<T>::operator()(T Lhs, T Rhs) const
{
	return Lhs < Rhs;
}

#endif 
