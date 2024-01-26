


// LinkedList class should go in the "ufl_cap4053::fundamentals" namespace!
//Some resources I used to help me remember how to write a linked list and how to do an iteraotr class:
// stackoverflow.com/questions/55402803/linked-list-iterator-implementation-c
//  geeksforgeeks.org/introduction-and-insertion-in-a-doubly-linked-list/#
namespace ufl_cap4053 {
	namespace fundamentals {

		template<class T>
		class LinkedList {
			
			struct Node {
				T data;
				Node* prev;
				Node* next;

				Node(T datas) {
					data = datas;
					prev = nullptr;
					next = nullptr;
				}
			};
			Node* head;
			Node* tail;

		public:
			//A TA helped me grasp the iterator class so credit to them
			class Iterator {
				
				Node* iter;

			public:
				Iterator(Node* temp) {
					iter = temp;
				}

				T operator*() const {
					return iter->data;
				}

				Iterator& operator++() {
					if (iter->next != nullptr) {
						iter = iter->next;
						return *this;
					}
					else {
						iter = nullptr;
						return *this;
					}
				}

				bool operator==(Iterator const& rhs) {
					if (rhs.iter == iter) {
						return true;
					}
					else {
						return false;
					}
				}

				bool operator!=(Iterator const& rhs) {
					if (rhs.iter != iter) {
						return true;
					}
					else {
						return false;
					}
				}
			};

			LinkedList<T>() {
				head = nullptr;
				tail = nullptr;
			}
			~LinkedList(){
				clear();
			}


			Iterator begin() const {
				return Iterator(head);
				
			}

			Iterator end() const {
				if (tail != nullptr) {
					return Iterator(tail->next);
				}
				else {
					return Iterator(nullptr);
				}
			}

			bool isEmpty() const {
				if (head == nullptr) {
					return true;
				}
				else {
					return false;
				}
			}

			T getFront() const {
				return head->data;
			}

			T getBack() const {
				return tail->data;
			}

			void enqueue(T element) {
				Node* temp = new Node(element);
				if (head == nullptr) {
					head = temp;
					tail = temp;
				}
				else {
					tail->next = temp;
					temp->prev = tail;
					tail = temp;
				}
			}

			void dequeue() {
				if (head != nullptr) {
					Node* temp = head;
					head = head->next;
					
					if (head == nullptr) {
						tail = head;
					}
					else {
						head->prev = nullptr;
					}
					delete temp;
				}
			}

			void pop() {
				if (tail->data != nullptr) {
					Node* temp = tail;
					tail = tail->prev;
					
					if (tail == nullptr) {
						head = tail;
					}
					else {
						tail->next = nullptr;
					}
					delete temp;
				}
			}

			void clear() {
				Node* temp = head;
				while (temp != nullptr) {
					Node* follow = temp;
					temp = temp->next;
					delete follow;
				}
				head = nullptr;
				tail = nullptr;
				
			}

			bool contains(T element) const {
				Node* temp = head;
				while (temp != nullptr) {
					if (temp->data == element) {
						return true;
					}
					temp = temp->next;
				}
				return false;
			}

			void remove(T element) {
				Node* temp = head;
				while (temp != nullptr) {
					if (temp->data == element) {

						if (temp->prev != nullptr) {
							temp->prev->next = temp->next;
						}
						else {
							head = head->next;
						}

						if (temp->next != nullptr) {
							temp->next->prev = temp->prev;
						}
						else {
							tail = temp->prev;
						}
						delete temp;
						break;
					}
					temp = temp->next;
				}
			}


		};


	}
}  // namespace ufl_cap4053::fundamentals
