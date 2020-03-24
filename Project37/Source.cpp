#include<iostream>
#include<queue>
using namespace std;

struct node // ��������� ��� ������������� ����� ������
{
	int key;//�������� ����
	unsigned char height;//������ ��������� � ������ � ������ ����
	node* left;//��������� �� ����� ���������
	node* right;//��������� �� ������ ���������
	node(int k) { key = k; left = right = 0; height = 1; }//����������� ����� ���� � ������� 1
};

unsigned char height(node* p)//������� ���������� ������
{
	if (!p)//���� ������
		return 0;//������� 0
	else//�����
		return p->height;//������� ������
	//return p ? p->height : 0;
}

int bfactor(node* p)//��������� ������ ������ ����
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)//�������������� ���������� �������� ������
{
	unsigned char hl = height(p->left);//������ ������
	unsigned char hr = height(p->right);//������ �������
	p->height = (hl > hr ? hl : hr) + 1;//���� h1 > hr �� h1 + 1 ����� hr + 1
}

node* rotateright(node* p) // ������ ������� ������ p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // ����� ������� ������ q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // ������������ ���� p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // ������������ �� �����
}

node* insert(node* p, int k) // ������� ����� k � ������ � ������ p
{
	if (!p) return new node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) // ����� ���� � ����������� ������ � ������ p 
{
	return p->left ? findmin(p->left) : p;
}

node* removemin(node* p) // �������� ���� � ����������� ������ �� ������ p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) // �������� ����� k �� ������ p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}



void levelOrder(node* x) {
	if (x == NULL)
		// ����������, ���� ���� �������
		return;

	// queue 
	queue<node*> q;
	node* curr;

	// push x 
	q.push(x);

	while (!q.empty()) {
		// ���� q �� �����
		// �������� ������� 
		curr = q.front();
		q.pop();

		// ������� �������� ����
		cout << curr->key << " ";

		// ��������� ������� � �������
		if (curr->left != NULL)
			q.push(curr->left);
		if (curr->right != NULL)
			q.push(curr->right);
	}
}

bool search(const int x, node* tree)
{
	if (tree == NULL)
	{
		return false;
	}
	else if (x < tree->key)
	{
		return search(x, tree->left);
	}
	else if (tree->key < x)
	{
		return search(x, tree->right);
	}
	else
	{
		;
	}
}


void preOrder(node* root)
{
	if (root != NULL)
	{
		cout << root->key << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
	else cout << "������ ������" << endl;
}
int main() {
	setlocale(LC_ALL, "rus");
	int ch, y = 0;
	int x;
	node* p = NULL;
	do
	{
		cout << "\n\t ������ ������ ������";
		cout << "\n 1. ������� ������� ";
		cout << "\n 2. �������� �������";
		cout << "\n 3. ����� ������ ";
		cout << "\n 4. ����� ";
		cout << "\n����� ��������: "; cin >> ch;
		switch (ch)
		{
		case 1:
			cout << "������� ��������: ";
			cin >> x;
			p=insert(p,x);
			cout << "\n������� ����������.\n";
			break;
		case 2:
			cout << "������� ��������: ";
			cin >> x;
			if (search(x, p))
				p = remove(p, x);
			else
				cout << "������� �� �������";
			break;
		
		case 3:
			cout << "�������� ����� " << endl;
			cout << "1)InOrder" << endl << "2)levelOrder" << endl;
			cin >> x;
			if (x == 1) {
				preOrder(p);
				break;
			}
			else levelOrder(p);
			break;



		case 4: y = 1;
			break;
		default: cout << "\n����� ��������.";
		}
		cout << endl;

	} while (y != 1);
	return 1;
	
	
}