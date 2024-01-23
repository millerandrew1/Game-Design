

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

		void breadthFirstTraverse(void (*dataFunction)(const T)) const {

		}

		void preOrderTraverse(void (*dataFunction)(const T)) const {

		}

		void postOrderTraverse(void (*dataFunction)(const T)) const {

		}

	};
}}  // namespace ufl_cap4053::fundamentals
