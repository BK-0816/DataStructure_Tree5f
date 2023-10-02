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
			printf("검색 성공:%d\n", key);
			printf("방문한 노드의 수: %d\n", count);
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
	printf("검색 실패!!\n");
	return NULL; 	// 탐색에 실패했을 경우 NULL 반환

}

TreeNode* new_node(int item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int key, int* count)
{		// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) {
		(*count)++;
		return new_node(key);
	}
	(*count)++;
	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (key < node->key) {
		node->left = insert_node(node->left, key, count);

	}
	else if (key > node->key) {
		node->right = insert_node(node->right, key, count);

	}
	// 변경된 루트 포인터를 반환한다.
	return node;
}
TreeNode* insert_node2(TreeNode* node, int key, int* count)
{
	TreeNode* newNode = new_node(key); // 새로운 노드를 만듭니다.
	if (node == NULL) {
		(*count)++;
		return newNode; // 트리가 비어있으면 새로운 노드를 반환하여 트리의 루트로 만듭니다.
	}
	(*count)++;
	while (1) {
		if (key < node->key) {
			if (node->left == NULL) {
				node->left = newNode; // 왼쪽 자식이 없으면 새로운 노드를 왼쪽 자식으로 추가합니다.
				return newNode; // 노드 삽입 후 종료합니다.
			}
			node = node->left; // 왼쪽 자식으로 이동합니다.

		}
		else if (key > node->key) {
			if (node->right == NULL) {
				node->right = newNode; // 오른쪽 자식이 없으면 새로운 노드를 오른쪽 자식으로 추가합니다.
				return newNode; // 노드 삽입 후 종료합니다.
			}
			node = node->right; // 오른쪽 자식으로 이동합니다.

		}
		else {
			// 이미 같은 키가 있는 경우 아무 작업도 하지 않고 반환합니다.
			free(newNode); // 중복된 키를 가진 노드를 해제합니다.
			return node; // 기존 노드를 반환합니다.
		}
		count++;
	}
}


TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;

	return current;
}

TreeNode* delete_node(TreeNode* node, int key, int* count)
{
	if (node == NULL)
		return node;

	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (key < node->key) {
		node->left = delete_node(node->left, key, count);

	}
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (key > node->key) {
		node->right = delete_node(node->right, key, count);

	}
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else {
		// 첫 번째나 두 번째 경우
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
		// 세 번째 경우
		TreeNode* temp = min_value_node(node->right);

		// 중외 순회시 후계 노드를 복사한다. 
		node->key = temp->key;
		// 중외 순회시 후계 노드를 삭제한다. 
		node->right = delete_node(node->right, temp->key, count);

		(*count)++;
	}

	return node;
}
TreeNode* delete_node2(TreeNode* node, int key)
{
	TreeNode* parent = NULL; // 삭제할 노드의 부모를 저장할 변수
	TreeNode* current = node; // 현재 노드를 가리킬 변수
	int count = 0;
	// 키를 찾을 때까지 순회
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

	// 키를 찾지 못한 경우
	if (current == NULL) {
		printf("삭제할 노드를 찾지 못했습니다.\n");
		return node;
	}

	// 삭제할 노드를 찾은 경우
	printf("방문한 노드의 수: %d\n", count);
	// 첫 번째나 두 번째 경우 (자식이 없거나 하나만 있는 경우)
	if (current->left == NULL || current->right == NULL) {
		TreeNode* temp = NULL;

		// 자식이 없는 경우
		if (current->left == NULL) {
			temp = current->right;
		}
		else {
			temp = current->left;
		}

		// 부모 노드의 자식 포인터를 변경
		if (parent == NULL) {
			// 삭제할 노드가 루트인 경우
			free(current);
			printf("방문한 노드의 수:%d", count);
			return temp; // 새로운 루트를 반환
		}
		else if (current == parent->left) {
			parent->left = temp;
		}
		else {
			parent->right = temp;
		}

		free(current); // 노드 메모리 해제
	}
	else {
		// 세 번째 경우 (자식이 둘 다 있는 경우)
		TreeNode* successor = min_value_node(current->right); // 후계자 노드 찾기
		current->key = successor->key; // 후계자 노드의 키를 현재 노드로 복사
		current->right = delete_node2(current->right, successor->key); // 후계자 노드 삭제

	}

	return node;

}

void inorder(TreeNode* node) {
	if (node) {
		inorder(node->left);  // 왼쪽 서브트리 순회
		printf("%d ", node->key);      // 노드 방문
		// 노드 개수 증가
		inorder(node->right); // 오른쪽 서브트리 순회
	}
}

int main() {
	char menu = 0;
	int key = 0;
	int count = 0;

	printf("-----------------\n");
	printf("   s    : 검색\n");
	printf("   i    : 노드 추가\n");
	printf("   d    : 노드 삭제\n");
	printf("   t    : 중위 순회\n");
	printf("   I    : 노드 추가(반복)\n");
	printf("   D    : 노드 삭제(반복)\n");
	printf("   c    : 종료\n");
	printf("-----------------\n");

	while (menu != 'c') {
		printf("\n");
		printf("\n");
		printf("메뉴 입력: ");
		scanf_s(" %c", &menu);

		switch (menu) {
		case 's':
			printf("검색할 값 입력:");
			scanf_s("%d", &key);
			search(node, key);
			inorder(node);
			break;
		case 'i':
			printf("삽입할 값 입력:");
			scanf_s("%d", &key);
			node = insert_node(node, key, &count);
			printf("방문한 노드의 수: %d\n", count);
			inorder(node);
			break;
		case 'd':
			printf("삭제할 값 입력:");
			scanf_s("%d", &key);
			delete_node(node, key, &count);
			printf("방문한 노드의 수: %d\n", count);
			inorder(node);
			break;

		case 't':
			inorder(node);
			break;
		case 'I':
			printf("삽입할 값 입력:");
			scanf_s("%d", &key);
			insert_node2(node, key, &count);
			printf("방문한 노드의 수: %d\n", count);
			inorder(node);
			break;
		case 'D':
			printf("삭제할 값 입력:");
			scanf_s("%d", &key);
			delete_node2(node, key);
			inorder(node);
			break;
		case 'c':
			printf("프로그램을 종료합니다.\n");
			break;
		default:
			printf("잘못된 메뉴 선택입니다. 다시 시도하세요.\n");
		}
	}
	count = 0;
	return 0;
}
