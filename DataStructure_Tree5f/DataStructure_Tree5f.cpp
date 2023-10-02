#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
	int key;
	struct TreeNode* left, * right;

} TreeNode;
TreeNode n1 = { 25, NULL, NULL };
TreeNode n2 = { 16, NULL, &n1 };
TreeNode n3 = { 42, NULL, NULL };
TreeNode n4 = { 46, &n3, NULL };
TreeNode n5 = { 55, NULL, NULL };
TreeNode n6 = { 53, &n4, &n5 };
TreeNode n7 = { 41, &n2, &n6 };;
TreeNode n8 = { 62, NULL, NULL };
TreeNode n9 = { 64, NULL, NULL };
TreeNode n10 = { 63, &n8, &n9 };
TreeNode n11 = { 70, NULL, NULL };
TreeNode n12 = { 65, &n10, &n11 };
TreeNode n13 = { 74, &n12, NULL };
TreeNode n14 = { 60, &n7, &n13 };
TreeNode* node = &n14;

TreeNode* search(TreeNode* node, int key)
{
	int count = -1;
	while (node != NULL) {
		if (key == node->key) {
			printf("�˻� ����:%d\n", key);
			printf("�湮�� ����� ��: %d\n", count);
			return node;
		}
		else if (key < node->key) {
			node = node->left;
			count++;
		}
		else
			node = node->right;
		count++;
	}
	printf("�˻� ����!!\n");
	return NULL; 	// Ž���� �������� ��� NULL ��ȯ

}

TreeNode* new_node(int item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int key, int* count)
{		// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) {
		(*count)++;
		return new_node(key);
	}
	(*count)++;
	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (key < node->key) {
		node->left = insert_node(node->left, key, count);

	}
	else if (key > node->key) {
		node->right = insert_node(node->right, key, count);

	}
	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�.
	return node;
}
TreeNode* insert_node2(TreeNode* node, int key, int* count)
{
	TreeNode* newNode = new_node(key); // ���ο� ��带 ����ϴ�.
	if (node == NULL) {
		(*count)++;
		return newNode; // Ʈ���� ��������� ���ο� ��带 ��ȯ�Ͽ� Ʈ���� ��Ʈ�� ����ϴ�.
	}
	(*count)++;
	while (1) {
		if (key < node->key) {
			if (node->left == NULL) {
				node->left = newNode; // ���� �ڽ��� ������ ���ο� ��带 ���� �ڽ����� �߰��մϴ�.
				return newNode; // ��� ���� �� �����մϴ�.
			}
			node = node->left; // ���� �ڽ����� �̵��մϴ�.

		}
		else if (key > node->key) {
			if (node->right == NULL) {
				node->right = newNode; // ������ �ڽ��� ������ ���ο� ��带 ������ �ڽ����� �߰��մϴ�.
				return newNode; // ��� ���� �� �����մϴ�.
			}
			node = node->right; // ������ �ڽ����� �̵��մϴ�.

		}
		else {
			// �̹� ���� Ű�� �ִ� ��� �ƹ� �۾��� ���� �ʰ� ��ȯ�մϴ�.
			free(newNode); // �ߺ��� Ű�� ���� ��带 �����մϴ�.
			return node; // ���� ��带 ��ȯ�մϴ�.
		}
		count++;
	}
}


TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;

	return current;
}

TreeNode* delete_node(TreeNode* node, int key, int* count)
{
	if (node == NULL)
		return node;

	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (key < node->key) {
		node->left = delete_node(node->left, key, count);

	}
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (key > node->key) {
		node->right = delete_node(node->right, key, count);

	}
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		// ù ��°�� �� ��° ���
		if (node->left == NULL) {
			TreeNode* temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL) {
			TreeNode* temp = node->left;
			free(node);
			return temp;
		}
		// �� ��° ���
		TreeNode* temp = min_value_node(node->right);

		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		node->key = temp->key;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		node->right = delete_node(node->right, temp->key, count);

		(*count)++;
	}

	return node;
}
TreeNode* delete_node2(TreeNode* node, int key)
{
	TreeNode* parent = NULL; // ������ ����� �θ� ������ ����
	TreeNode* current = node; // ���� ��带 ����ų ����
	int count = 0;
	// Ű�� ã�� ������ ��ȸ
	while (current != NULL && current->key != key) {
		parent = current;

		if (key < current->key) {
			current = current->left;

		}
		else if (key > current->key) {
			current = current->right;
			count++;
		}
	}

	// Ű�� ã�� ���� ���
	if (current == NULL) {
		printf("������ ��带 ã�� ���߽��ϴ�.\n");
		return node;
	}

	// ������ ��带 ã�� ���
	printf("�湮�� ����� ��: %d\n", count);
	// ù ��°�� �� ��° ��� (�ڽ��� ���ų� �ϳ��� �ִ� ���)
	if (current->left == NULL || current->right == NULL) {
		TreeNode* temp = NULL;

		// �ڽ��� ���� ���
		if (current->left == NULL) {
			temp = current->right;
		}
		else {
			temp = current->left;
		}

		// �θ� ����� �ڽ� �����͸� ����
		if (parent == NULL) {
			// ������ ��尡 ��Ʈ�� ���
			free(current);
			printf("�湮�� ����� ��:%d", count);
			return temp; // ���ο� ��Ʈ�� ��ȯ
		}
		else if (current == parent->left) {
			parent->left = temp;
		}
		else {
			parent->right = temp;
		}

		free(current); // ��� �޸� ����
	}
	else {
		// �� ��° ��� (�ڽ��� �� �� �ִ� ���)
		TreeNode* successor = min_value_node(current->right); // �İ��� ��� ã��
		current->key = successor->key; // �İ��� ����� Ű�� ���� ���� ����
		current->right = delete_node2(current->right, successor->key); // �İ��� ��� ����

	}

	return node;

}

void inorder(TreeNode* node) {
	if (node) {
		inorder(node->left);  // ���� ����Ʈ�� ��ȸ
		printf("%d ", node->key);      // ��� �湮
		// ��� ���� ����
		inorder(node->right); // ������ ����Ʈ�� ��ȸ
	}
}

int main() {
	char menu = 0;
	int key = 0;
	int count = 0;

	printf("-----------------\n");
	printf("   s    : �˻�\n");
	printf("   i    : ��� �߰�\n");
	printf("   d    : ��� ����\n");
	printf("   t    : ���� ��ȸ\n");
	printf("   I    : ��� �߰�(�ݺ�)\n");
	printf("   D    : ��� ����(�ݺ�)\n");
	printf("   c    : ����\n");
	printf("-----------------\n");

	while (menu != 'c') {
		printf("\n");
		printf("\n");
		printf("�޴� �Է�: ");
		scanf_s(" %c", &menu);

		switch (menu) {
		case 's':
			printf("�˻��� �� �Է�:");
			scanf_s("%d", &key);
			search(node, key);
			inorder(node);
			break;
		case 'i':
			printf("������ �� �Է�:");
			scanf_s("%d", &key);
			node = insert_node(node, key, &count);
			printf("�湮�� ����� ��: %d\n", count);
			inorder(node);
			break;
		case 'd':
			printf("������ �� �Է�:");
			scanf_s("%d", &key);
			delete_node(node, key, &count);
			printf("�湮�� ����� ��: %d\n", count);
			inorder(node);
			break;

		case 't':
			inorder(node);
			break;
		case 'I':
			printf("������ �� �Է�:");
			scanf_s("%d", &key);
			insert_node2(node, key, &count);
			printf("�湮�� ����� ��: %d\n", count);
			inorder(node);
			break;
		case 'D':
			printf("������ �� �Է�:");
			scanf_s("%d", &key);
			delete_node2(node, key);
			inorder(node);
			break;
		case 'c':
			printf("���α׷��� �����մϴ�.\n");
			break;
		default:
			printf("�߸��� �޴� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
		}
	}
	count = 0;
	return 0;
}
