#include <queue>
#include <stack>
using namespace std;


// TreeNode class should go in the "ufl_cap4053::fundamentals" namespace!
//Used this to help formulate how to build the treenode class: 
// www.geeksforgeeks.org/generic-treesn-array-trees/
// www.studytonight.com/advanced-data-structures/nary-tree
namespace ufl_cap4053 { namespace fundamentals {

	template <class T>
	class TreeNode {
	public:
		T data;
		TreeNode<T>* currChild;
		TreeNode<T>* sibling;

		
		
		TreeNode() {
			data = nullptr;
			currChild = nullptr;
			sibling = nullptr;
		}

		TreeNode(T datas) {
			data = datas;
			currChild = nullptr;
			sibling = nullptr;
		}

		const T& getData() const {
			return data;
		}

		size_t getChildCount() const {
			size_t num = 0;
			TreeNode* temp = currChild;
			
			if (currChild == nullptr) {
				return num;
			}
			num++;
			
			while (temp->sibling != nullptr) {
				num++;
				temp = temp->sibling;
			}
			return num;

		}

		TreeNode<T>* getChild(size_t index) {
			if (index == 0) {
				return currChild;
			}
			else {
				TreeNode* temp = currChild;
				size_t num = 0;
				while (num != index) {
					if (temp->sibling != nullptr) {
						num++;
						temp = temp->sibling;
					}
					else {
						return nullptr;
					}
				
				}
				return temp;
			}
		}

		TreeNode<T>* getChild(size_t index) const{
			if (index == 0) {
				return currChild;
			}
			else {
				TreeNode* temp = currChild;
				size_t num = 0;
				while (num != index) {
					if (temp->sibling != nullptr) {
						num++;
						temp = temp->sibling;
					}
					else {
						return nullptr;
					}

				}
				return temp;
			}
		}

		void addChild(TreeNode<T>* child) {
			if (currChild == nullptr) {
				currChild = child;
			}
			else {
				TreeNode* temp = currChild;
				while (temp->sibling != nullptr)
				{
					temp = temp->sibling;
				}
				temp->sibling = child;
			}
		}

		TreeNode<T>* removeChild(size_t index) {
			TreeNode* temp = currChild;

			if (index == 0) {
				
				if (temp != nullptr) {
					currChild = currChild->sibling;
					temp->sibling = nullptr;
				}
				return temp;
			}
			else {
				size_t currIndex = 0;

				while (currIndex != index-1) {
					if (temp != nullptr) {
						temp = temp->sibling;
						currIndex++;
					}
					else {
						break;
					}
				}
				if (temp->sibling == nullptr) {
					return nullptr;
				}
				else {
					TreeNode* newTemp = temp->sibling;
					temp->sibling = newTemp->sibling;
					newTemp->sibling = nullptr;
					return newTemp;
				}

			}
		}

		//Used this link to help me remember how to set up the breadthFirstTraverse
		//stackoverflow.com/questions/17939247/breadth-first-traversal-with-binary-search-tree-c
		void breadthFirstTraverse(void (*dataFunction)(const T)) const {
		
			if (this != nullptr) {
				dataFunction(this->data);
			}

			queue<TreeNode<T>*> q;
			
			q.push(this->currChild);
			TreeNode* temp = this->currChild;
			while (temp->sibling != nullptr) {
				temp = temp->sibling;
				q.push(temp);
			}
			
			while (!q.empty()) {
				temp = q.front();
				q.pop();
				dataFunction(temp->data);

				if (temp->currChild != nullptr) {
					temp = temp->currChild;
					q.push(temp);
					while (temp->sibling != nullptr) {
						temp = temp->sibling;
						q.push(temp);
					}
				}
			}
/*

			if (this != nullptr) {
				dataFunction(this->data);
				size_t num = getChildCount();
				TreeNode* temp = this->currChild;
				TreeNode* curr = temp;
				while (num != 0) {
					while (curr != nullptr) {
						dataFunction(curr->data);
						curr = curr->sibling;
					}
					num = 0;
					curr = temp;
					
					while (num == 0) {
						if (curr->sibling == nullptr) {
							break;
						}
						curr = curr->sibling;
						num = curr->getChildCount();
					}

					
					temp = curr;
					curr = curr->currChild;
				}

			}

	*/		
		}

		void preOrderTraverse(void (*dataFunction)(const T)) const {

			if (this != nullptr) {
				dataFunction(this->data);
			}
			size_t num = 0;
			queue<TreeNode<T>*> q;

			q.push(this->currChild);
			TreeNode* temp = this->currChild;
			TreeNode* top = this->currChild;

			while (!q.empty()) {
				temp = q.front();
				q.pop();
				dataFunction(temp->data);
				
				if (temp->currChild != nullptr) {
					top = temp;
					temp = temp->currChild;
				}
				else if (temp->sibling != nullptr){
					temp = temp->sibling;
				}
				else {
					temp = top->sibling;
				}
				if (temp != nullptr) {
					q.push(temp);
				}
			}

		}

		void postOrderTraverse(void (*dataFunction)(const T)) const {
			

			stack<TreeNode<T>*> s;
			
			s.push(this->currChild);
			TreeNode* temp = this->currChild;
			TreeNode* top = this->currChild;
			size_t num = this->getChildCount();
			bool checked = false;

			while (!s.empty()) {
				
				
				if (temp->currChild != nullptr && !checked) {
					top = temp;
					s.push(temp->currChild);
					temp = temp->currChild;
					
				}
				else {
					temp = s.top();
					dataFunction(temp->data);
					s.pop();
					if (temp->sibling != nullptr) {
						temp = temp->sibling;
						s.push(temp);
						
					}
					else if (temp->sibling == nullptr && temp->currChild != nullptr) {
						checked = true;
					}
					
					
				}
			}
			dataFunction(this->data);
		}

	};
}}  // namespace ufl_cap4053::fundamentals
