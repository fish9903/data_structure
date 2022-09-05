#include "ptyqueue.h"

template <class DT>
PtyQueue<DT>::PtyQueue(int maxNumber)
	:Heap<DT> (maxNumber)
{
	
}

template<class DT>
void PtyQueue<DT>::enqueue(const DT& newDataItem)
{
	this->insert(newDataItem);
}

template<class DT>
DT PtyQueue<DT>::dequeue()
{
	
	return this->removeMax();
}
