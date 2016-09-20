#include <stdio.h>
#include <stdlib.h>
struct list{
//Variables
	struct node{
		node* next;
		node* previous;
		int num;
	};
	node* first;
	node* last;
	int len;
//Constructors
	explicit list(){
		len = 0;
		first = (node*)malloc(sizeof(node));
	}
	//Operator=
	void operator=(list l){
		for(int i = 0; i < l.size(); i++)
			add(i, l.get(i));
	}
//Helpful methods
	//Initiate first node
	void init(int num){
		first->num = num;
		last = first;
		len++;
	}
	//Get address for any index
	node* ad(int index){
		node* n = first;
		for(int i = 0; i < index; i++){
			n = n->next;
		}
		return n;
	}
//All add methods
	//Insert element at beginning
	void push_front(int num){
		//If first node
		if(!len) return init(num);
		//Construct new node
		node* n = first;
		first = (node*)malloc(sizeof(node));
		//Change first node to new node
		first->next = n;
		first->num = num;
		//Change address of old first node
		n->previous = first;
		//Increment length
		len++;
	}
	//Add element at the end
	void push_back(int num){
		//If first node
		if(!len) return init(num);
		//Construct new node
		node* n = (node*)malloc(sizeof(node));
		//Add new node
		n->num = num;
		n->previous = last;
		last->next = n;
		last = n;
		//Increment length
		len++;
	}
	//Insert element anywhere in the list on the index
	void add(int index, int num){
		//Conditions
		if(index < 0) return;
		if(!len) return init(num);
		if(index >= len) return push_back(num);
		if(index == 0) return push_front(num);
		//Go to indexed node
		node* address = ad(index-1);
		//Construct new node
		node* n = (node*)malloc(sizeof(node));
		//Add new node
		n->previous = address;
		n->next = address->next;
		n->num = num;
		//Change previous and next node
		address->next = n;
		n->next->previous = n;
		//Increment length
		len++;
	}
	//Add another list to the end of this list
	void add(list l){
		for(int i = 0; i < l.size(); i++)
			push_back(l.get(i));
	}
//All remove methods
	//Delete first element
	void pop_front(){
		//Conditions
		if(len == 0) return;
		if(len == 1){
			len--;
			return;
		}
		//Store address of first node for removal
		first = first->next;
		free(first->previous);
		//Decrement length;
		len--;
	}
	//Delete last element
	void pop_back(){
		//Conditions
		if(len == 0) return;
		if(len == 1){
			len--;
			return;
		}
		//Store address of last node for removal
		node* n = last;
		last = last->previous;
		free(n);
		//Decrement length;
		len--;
	}
	//Remove element anywhere in the list on the index
	void remove(int index){
		//Conditions
		if(index >= len || index < 0) return;
		if(index == 0) return pop_front();
		if(index == len-1) return pop_back();
		//Go to index address
		node* address = ad(index);
		//Change previous and next nodes
		address->previous->next = address->next;
		address->next->previous = address->previous;
		//Remove node
		free(address);
		//Decrement length
		len--;
	}
	//Remove element based on address
	void remove(node* ad){
		//Conditions
		if(ad == first) return pop_front();
		if(ad == last) return pop_back();
		//Remove node
		ad->previous->next = ad->next;
		ad->next->previous = ad->previous;
		free(ad);
		//Decrement length
		len--;
	}
//Swap method
	//Will not swap if any index is bigger than length and smaller than 0
	void swap(int index1, int index2){
		//Condition
		if(index1 >= len || index1 < 0 || index2 >= len || index2 < 0)
			return;
		//Get address of both nodes
		node* address1 = ad(index1);
		node* address2 = ad(index2);
		//Swap
		int n = address1->num;
		address1->num = address2->num;
		address2->num = n;
	}
	//Swapping based on addresses
	void swap(node* address1, node* address2){
		int n = address1->num;
		address1->num = address2->num;
		address2->num = n;
	}
//Sort method
	//Good old bubble sort on a range of data
	void sort(int index1, int index2){
		//Conditions
		if(index1 < 0) index1 = 0;
		if(index1 > len) index1 = len;
		if(index2 < 0) index2 = 0;
		if(index2 > len) index2 = len;
		if(index2 <= index1) return;
		//Bubble sort
		node* i;
		node* j;
		i = ad(index1);
		node* end = ad(index2);
		while(i != end){
			j = i;
			while(j != end){
				if(j->num < i-> num)
					swap(i, j);
				j = j->next;
			}
			i = i->next;
		}
	}
//Reverse method
	//Reverse the order of elements on the range of data
	//Note: reverse only up to index2, does not reverse with index2
	void reverse(int index1, int index2){
		//Conditions
		if(index1 < 0) index1 = 0;
		if(index1 > len) index1 = len;
		if(index2 < 0) index2 = 0;
		if(index2 > len) index2 = len;
		if(index2 <= index1) return;
		//Reverse
		int half = (index2-index1)/2;
		node* ad1 = ad(index1);
		node* ad2 = ad(index2-1);
		for(int i = 0; i < half; i++){
			swap(ad1, ad2);
			ad1 = ad1->next;
			ad2 = ad2->previous;
		}
	}
//Unique method
	//Removes all duplicated elements
	void unique(){
		node* current = first;
		for(int i = 1; i < len; i++){
			node* temp = current->next;
			while(temp != last->next){
				if(current->num == temp->num){
					temp = temp->previous;
					remove(temp->next);
				}
				temp = temp->next;
			}
			current = current->next;
		}
	}
//All access methods
	int front(){return first->num;}
	int back(){return last->num;}
	//Get indexed int, return -1 if index out of bounds
	int get(int index){
		//Get address of index
		if(index >= len || index < 0)
			return -1;
		node* address = ad(index);
		return address->num;
	}
//All size methods
	//Check if this list is empty
	bool empty(){
		if(len)
			return false;
		else
			return true;
	}
	//Return size of this list
	int size(){return len;}
//Clear method
	//Complete destroys everything in this list
	void clear(){
		while(!empty())
			pop_back();
	}
//Print method
	//Prints everything in the list
	void print(){
		node* n = first;
		for(int i = 0; i < len; i++){
			printf("%d ", n->num);
			n = n->next;
		}
		printf("\n");
	}
};
int main(){
	list l;
	printf("Here's a demonstration of my linked list.\n");
	printf("For variables, it simply contains nodes, the first and last node address, and the size of the list.\n");
	printf("Helpful tools include initiation for the first node, and a method that can get any node's address based on its index, time complexity: O(n).\n");
	printf("Let's get on with the point. I'll now demonstrate adding numbers into this linked list.\n");
	printf("\n");

	printf("-This is push_front, which adds an element to the beginning of the list.\n");
	printf("-Time complexity: O(1)\n");
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Now adding the integer 3\n");
	l.push_front(3);
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("\n");

	printf("-This is push_back, which adds an element to the end of the list.\n");
	printf("-Time complexity: O(1)\n");
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Now adding the integer 10\n");
	l.push_back(10);
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("\n");

	printf("-This is add, which adds an element to the index of the list.\n");
	printf("-Time complexity: O(n), due to searching time\n");
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Now adding the integer 4 to index 1\n");
	l.add(1, 4);
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Notice that it added to index 1 and moved the 10 to the side, it does not replace the 10.\n");
	printf("It will not anything to an index less than 0, but it will to the back for any index same or bigger than current length.\n");
	printf("Consider:\n");
	printf("Now adding the integer 6 to index -10\n");
	l.add(-10, 6);
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Now adding the integer 6 to index 10\n");
	l.add(10, 6);
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("\n");

	printf("I'll now add more elements to the list to demonstrate remove methods.\n");
	l.push_back(3);
	l.push_back(0);
	l.push_back(1);
	l.push_back(7);
	l.push_back(8);
	l.push_back(13);
	l.push_back(5234);
	l.push_front(4589);
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("\n");

	printf("-This is pop_front, which removes an element from the beginning of the list.\n");
	printf("-Time complexity: O(1)\n");
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Removing first element...\n");
	l.pop_front();
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("\n");

	printf("-This is pop_back, which removes an element from the end of the list.\n");
	printf("-Time complexity: O(1)\n");
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Removing last element...\n");
	l.pop_back();
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("\n");

	printf("-This is remove, which removes the integer on that index.\n");
	printf("-Time complexity: O(n), by going to index for address\n");
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Removing index 5 element... Which was %d\n", l.get(5));
	l.remove(5);
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Notice that like a normal integer array, it removes not the 5th element, but the element on index 5.\n");
	printf("It will not remove anything out of bounds however.\n");
	printf("Removing index 12 element...\n");
	l.remove(12);
	printf("Removing index -3 element...\n");
	l.remove(-3);
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("\n");

	printf("-Now I'll demonstrate the swap method, which swaps 2 integers in the list based on their index.\n");
	printf("-Time complexity: O(2n), by going to index for address twice.\n");
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Swapping index 5 with index 7, which are %d and %d, respectively.\n", l.get(5), l.get(7));
	l.swap(5, 7);
	printf("\tList: ");
	l.print();
	printf("\n");

	printf("-Now I'll demonstrate the sort method, which sorts a range of integers in the list into non-decreasing order.\n");
	printf("-Time complexity: O(n^2), a bubble sort.\n");
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Sorting integers from index 3 up till 7...\n");
	l.sort(3, 7);
	printf("\tList: ");
	l.print();
	printf("Note: giving the range anything out of bounds will only not matter, because all range will be limited to 0 to max length in the list.\n");
	printf("For example: Sorting integers from index -9 up till 2384\n");
	l.sort(-9, 2384);
	printf("\tList: ");
	l.print();
	printf("Only sorts the whole list.\n");
	printf("\n");

	printf("-Now I'll demonstrate the reverse method, which reverses the aorder of a range of nodes in the list.\n");
	printf("-Time complexity: O(n)\n");
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Now reversing index 0 up till 6\n");
	l.reverse(0, 6);
	printf("\tList: ");
	l.print();
	printf("Like the sort method, giving any range out of bounds will not matter due to limitations.\n");
	printf("Now reversing index -20 up till 7\n");
	l.reverse(-20, 7);
	printf("\tList: ");
	l.print();
	printf("\n");

	printf("-Now I'll demonstrate the unique method, which removes any duplicates in the list, making it a set.\n");
	printf("-Time complexity: O(n^2)\n");
	printf("I'll add more duplicates in the list to demonstrate this method.\n");
	l.push_back(4);
	l.push_front(8);
	l.push_front(8);
	l.add(6, 7);
	l.add(3, 10);
	l.add(9, 13);
	l.push_back(1);
	l.push_back(6);
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("Removing duplicates...\n");
	l.unique();
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("\n");

	printf("-I'll simply demonstrate the access methods.\n");
	printf("\tThe first element, using front, is %d.\n", l.front());
	printf("\tThe last element, using back, is %d.\n", l.back());
	printf("-The get method, which gets any element based on its index, has a time complexity of O(n).\n");
	printf("Getting all numbers...\n");
	for(int i = 0; i < l.size(); i++)
		printf("\tThe index %d element is %d.\n", i, l.get(i));
	printf("\n");

	printf("-Now, let me demonstrate the operator =, which copies a list into another list.\n");
	list p;
	printf("For example, let p be the new list.\n");
	printf("\tSize of list(p): %d\n", p.size());
	printf("\tList(p): ");
	p.print();
	printf("Copying l into p...\n");
	p = l;
	printf("This is l.\n");
	printf("\tSize of list: %d\n", l.size());
	printf("\tList: ");
	l.print();
	printf("This is p.\n");
	printf("\tSize of list(p): %d\n", p.size());
	printf("\tList(p): ");
	p.print();
	printf("\n");

	printf("-Last but not least, I'll demonstrate the clear method and empty method.\n");
	printf("-Clear method, which removes everything, has a time complexity of O(n).\n");
	printf("-Empty method, which tells if the list is empty, has a time complexity of O(1).\n");
	printf("\tSize of list: %d\n", l.size());
	printf("\tIs the list empty? %s", l.empty() ? "Yes\n" : "No\n");
	printf("\tList: ");
	l.print();
	printf("Emptying...\n");
	l.clear();
	printf("\tSize of list: %d\n", l.size());
	printf("\tIs the list empty? %s", l.empty() ? "Yes\n" : "No\n");
	printf("\tList: ");
	l.print();
	printf("\n");

	printf("This concludes the demonstration of my linked list. Thank you very much for reading.\n");
	return 0;
}