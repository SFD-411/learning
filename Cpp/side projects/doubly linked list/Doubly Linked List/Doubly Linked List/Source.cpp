#include <cstdlib>
#include <iostream>
#include <string>

struct node
{
	std::string data;
	node* next;
	node* prev;
};

void printFro(node * head);
void printRev(node * tail);

int main(int argc, char** argv) {



	node* head;
	node* tail;
	node* n;

	n = new node;
	n->data = "this ";
	n->prev = NULL;
	head = n;
	tail = n;

	n = new node;
	n->data = "be ";
	n->prev = tail;
	tail->next = n;
	tail = n;

	n = new node;
	n->data = "here ";
	n->prev = tail;
	tail->next = n;
	tail = n;

	n = new node;
	n->data = "node ";
	n->prev = tail;
	tail->next = n;
	tail = n;
	tail->next = NULL;

	printFro(head);
	printRev(tail);

	return 0;
}

void printFro(node * head) 
{
	node* temp = head;
	while (temp != NULL)
	{
		std::cout << temp->data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;

}

void printRev(node * tail)
{
	node* temp = tail;
	while (temp != NULL)
	{
		std::cout << temp->data << " ";
		temp = temp->prev;
	}
	std::cout << std::endl;

}