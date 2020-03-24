#include<iostream>
#include<queue>
using namespace std;

struct node // структура для представления узлов дерева
{
	int key;//значение узла
	unsigned char height;//высота поддерева с корнем в данном узле
	node* left;//указатель на девое поддерево
	node* right;//указатель на правое поддерево
	node(int k) { key = k; left = right = 0; height = 1; }//конструктор новго узла с высотой 1
};

unsigned char height(node* p)//функция вычисления высоты
{
	if (!p)//если пустое
		return 0;//вернуть 0
	else//иначе
		return p->height;//вернуть высоту
	//return p ? p->height : 0;
}

int bfactor(node* p)//вычисляем баланс фактор узла
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)//востанавливает корректное значение высоты
{
	unsigned char hl = height(p->left);//высота левого
	unsigned char hr = height(p->right);//высота правого
	p->height = (hl > hr ? hl : hr) + 1;//если h1 > hr то h1 + 1 иначе hr + 1
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
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
	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
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
		// возвращаем, если узел нулевой
		return;

	// queue 
	queue<node*> q;
	node* curr;

	// push x 
	q.push(x);

	while (!q.empty()) {
		// пока q не пусто
		// удаление очереди 
		curr = q.front();
		q.pop();

		// выводим значение узла
		cout << curr->key << " ";

		// добавдяем ребенка в очередь
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
	else cout << "Дерево пустое" << endl;
}
int main() {
	setlocale(LC_ALL, "rus");
	int ch, y = 0;
	int x;
	node* p = NULL;
	do
	{
		cout << "\n\t Красно черное дерево";
		cout << "\n 1. Вставка вершины ";
		cout << "\n 2. Удаление вершины";
		cout << "\n 3. Выбор вывода ";
		cout << "\n 4. Выход ";
		cout << "\nВыбор действия: "; cin >> ch;
		switch (ch)
		{
		case 1:
			cout << "Введите значение: ";
			cin >> x;
			p=insert(p,x);
			cout << "\nВершина вставленна.\n";
			break;
		case 2:
			cout << "Введите значение: ";
			cin >> x;
			if (search(x, p))
				p = remove(p, x);
			else
				cout << "вершина не найдена";
			break;
		
		case 3:
			cout << "Выберите вывод " << endl;
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
		default: cout << "\nВыбор действия.";
		}
		cout << endl;

	} while (y != 1);
	return 1;
	
	
}