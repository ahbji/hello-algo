/**
 * File: min_heap.c
 * Created Time: 2023-01-15
 * Author: Reanon (793584285@qq.com)
 */

#include "../include/include.h"

#define MAX_SIZE 5000

/* 小顶堆 */
typedef struct minHeap
{
    // size 代表的是实际元素的个数
    int size;
    // 使用预先分配内存的数组，避免扩容
    int data[MAX_SIZE];
} minHeap;

void siftDown(minHeap *h, int i);

void siftUp(minHeap *h, int i);

/* 构造方法，根据切片建堆 */
minHeap *newMaxHeap(int nums[], int size)
{
    // 所有元素入堆
    minHeap *h = (minHeap *)malloc(sizeof(minHeap));
    h->size = size;
    memcpy(h->data, nums, size * sizeof(int));
    for (int i = size - 1; i >= 0; i--)
    {
        // 堆化除叶节点以外的其他所有节点
        siftDown(h, i);
    }
    return h;
}

/* 获取左子节点索引 */
int left(minHeap *h, int i)
{
    return 2 * i + 1;
}

/* 获取右子节点索引 */
int right(minHeap *h, int i)
{
    return 2 * i + 2;
}

/* 获取父节点索引 */
int parent(minHeap *h, int i)
{
    return (i - 1) / 2;
}

/* 交换元素 */
int swap(minHeap *h, int i, int j)
{
    int temp = h->data[i];
    h->data[i] = h->data[j];
    h->data[j] = temp;
}

/* 获取堆大小 */
int size(minHeap *h)
{
    return h->size;
}

/* 判断堆是否为空 */
int isEmpty(minHeap *h)
{
    return h->size == 0;
}

/* 访问堆顶元素 */
int peek(minHeap *h)
{
    return h->data[0];
}

/* 元素入堆 */
int push(minHeap *h, int val)
{
    // 默认情况下，不应该添加这么多节点
    if (h->size == MAX_SIZE)
    {
        printf("heap is full!");
        return NIL;
    }
    // 添加节点
    h->data[h->size] = val;
    h->size++;

    // 从底至顶堆化
    siftUp(h, h->size - 1);
}

/* 元素出堆 */
int pop(minHeap *h)
{
    // 判空处理
    if (isEmpty(h))
    {
        printf("heap is empty!");
        return NIL;
    }
    // 交换根节点与最右叶节点（即交换首元素与尾元素）
    swap(h, 0, size(h) - 1);
    // 删除节点
    int val = h->data[h->size - 1];
    h->size--;
    // 从顶至底堆化
    siftDown(h, 0);

    // 返回堆顶元素
    return val;
}

static void remove_item(int *nums, int size, int index)
{
    // 把 index 之后的所有元素向前移动一位
    for (int i = index; i < size - 1; i++)
    {
        nums[i] = nums[i + 1];
    }
    // reset 最后一个元素
    nums[size - 1] = NIL;
}

static int remove_at(minHeap *h, int index)
{
    if (isEmpty(h))
    {
        printf("heap is empty!");
        return NIL;
    }

    int index_of_last_elem = h->size - 1;
    int removed_data = h->data[index];
    swap(h, index, index_of_last_elem);
    remove_item(h->data, h->size, index_of_last_elem);
    if (index == index_of_last_elem)
        return removed_data;
    int elem = h->data[index];
    h->size--;
    siftDown(h, index);
    if (h->data[index] == elem)
        siftUp(h, index);
    return removed_data;
}

bool heap_remove(minHeap *h, int elem)
{
    if (elem == NIL)
        return false;
    for (int i = 0; i < h->size; i++)
    {
        if (elem == h->data[i])
        {
            remove_at(h, i);
            return true;
        }
    }
    return false;
}

/* 从节点 i 开始，从顶至底堆化 */
void siftDown(minHeap *h, int i)
{
    while (true)
    {
        // 判断节点 i, l, r 中值最小的节点，记为 min
        int l = left(h, i);
        int r = right(h, i);
        int min = l; // 假设 l 为最小的
        // 如果 r 更小，则将 r 设置为 min
        if (r < size(h) && h->data[r] < h->data[l])
        {
            min = r;
        }
        // 当 l 越界，或当前 i 节点不能再下沉，就停止循环。
        if (l >= size(h) || h->data[i] < h->data[min])
        {
            break;
        }
        // 交换两节点
        swap(h, min, i);
        // 循环向下堆化
        i = min;
    }
}

/* 从节点 i 开始，从底至顶堆化 */
void siftUp(minHeap *h, int i)
{
    while (true)
    {
        // 获取节点 i 的父节点
        int p = parent(h, i);
        // 当“越过根节点”或“节点无需修复”时，结束堆化
        if (p < 0 || h->data[i] >= h->data[p])
        {
            break;
        }
        // 交换两节点
        swap(h, i, p);
        // 循环向上堆化
        i = p;
    }
}

int main()
{
    /* 初始化堆 */
    // 初始化大顶堆
    int nums[] = {9, 8, 6, 6, 7, 5, 2, 1, 4, 3, 6, 2};
    minHeap *heap = newMaxHeap(nums, sizeof(nums) / sizeof(int));
    printf("输入数组并建堆后\n");
    printHeap(heap->data, heap->size);

    /* 获取堆顶元素 */
    printf("\n堆顶元素为 %d\n", peek(heap));

    /* 元素入堆 */
    push(heap, 7);
    printf("\n元素 7 入堆后\n");
    printHeap(heap->data, heap->size);

    /* 堆顶元素出堆 */
    int top = pop(heap);
    printf("\n堆顶元素 %d 出堆后\n", top);
    printHeap(heap->data, heap->size);

    heap_remove(heap, 5);
    printf("\n元素5 移除后\n");
    printHeap(heap->data, heap->size);

    while (heap->size != 0)
    {
        int top = pop(heap);
        printf("\n堆顶元素 %d 出堆后\n", top);
        printHeap(heap->data, heap->size);
    }
    printf("\n");

    /* 获取堆大小 */
    printf("\n堆元素数量为 %d\n", size(heap));

    /* 判断堆是否为空 */
    printf("\n堆是否为空 %d\n", isEmpty(heap));

    // 释放内存
    free(heap);
}