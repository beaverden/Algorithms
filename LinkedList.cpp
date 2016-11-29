template <class T>
class LinkedList
{
    public:
		LinkedList() 
		{
			this->first = nullptr;
			this->last = nullptr;
			this->length = 0;
		}

        virtual ~LinkedList() 
		{

			while (!this->empty())
			{
				this->remove(0);
			}
		}
  
		//Adds the element to the kth position
		void add(T val, int pos)
		{
			node *newNode = new node;
			newNode->val = val;
			if (this->length == 0)
			{
				if (pos == 0)
				{
					this->first = new node;
					this->first->val = val;
					this->last = this->first;
				}
			}
			else if (pos == this->length)
			{
				newNode->prev = this->last;
				this->last->next = newNode;
				this->last = newNode;
				
			}
			else if (pos == 0)
			{
				newNode->next = this->first;
				this->first->prev = newNode;
				this->first = newNode;
			}
			else
			{
				node* iterNode = this->first;
				int k = 0;
				while (iterNode && k < pos) 
				{
					iterNode = iterNode->next;
					k++;
				}
				
				if (iterNode->prev)
				{
					iterNode->prev->next = newNode;
				}
				newNode->prev = iterNode->prev;

				iterNode->prev = newNode;
				newNode->next = iterNode;
			}
			this->length++;
			newNode = nullptr;
		}

		//Removes the kth element from the list
		T remove(int k)
		{
			T returnValue;

			if (k == 0)
			{
				returnValue = this->first->val;
				node *nextLink = this->first->next;		
				delete this->first;
				if (this->length == 1)
				{
					this->first = nullptr;
					this->last = nullptr;
					this->iter = nullptr;
				}
				else
				{
					nextLink->prev = nullptr;
					this->first = nextLink;
				}	
				nextLink = nullptr;
			}
			else if (k == this->length - 1)
			{
				returnValue = this->last->val;
				node *prevLink = this->last->prev;
				delete this->last;
				if (this->length == 1)
				{
					this->first = nullptr;
					this->last = nullptr;
					this->iter = nullptr;
				}
				else
				{
					prevLink->next = nullptr;
					this->last = prevLink;
				}
				prevLink = nullptr;
			}
			else
			{
				node* iterator = this->first;
				int  currentPosition = 0;
				while (iterator && currentPosition < k)
				{
					iterator = iterator->next;
					currentPosition++;
				}
				returnValue = iterator->val;
				iterator->prev->next = iterator->next;
				delete iterator;
				iterator = nullptr;
			}
			this->length--;
			return returnValue;
		}


		//Returns the size of the list
		int size() 
		{
			return this->length;
		}

		//Returns whether the list is empty or not
		bool empty()
		{
			return (this->length == 0);
		}

		void iterator()
		{
			this->iter = this->first;
		}

		bool isNull()
		{
			return (this->iter == nullptr);
		}

		void next()
		{
			if (this->iter)
			{
				this->iter = this->iter->next;
			}
		}

		void prev()
		{
			if (this->iter)
			{
				this->iter = this->iter->prev;
			}
		}

		T curr()
		{
			return this->iter->val;
		}
		

	protected:
		struct node {
			T val;
			node *next = nullptr;
			node *prev = nullptr;
		};
		node *first;
		node *last;
		node *iter;
		int length;
};
