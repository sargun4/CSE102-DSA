def find_min(heap):
    return heap[0]
def create_heap():
    return []
def insert(x, heap):
    heap.append(x)
    bubble_up(len(heap) - 1, heap)
def extract_min(heap):
    heap[0], heap[-1] = heap[-1], heap[0]
    min_val = heap.pop()
    bubble_down(0, heap)
    return min_val
def decrease_key(p, delta, heap):
    heap[p] -= delta
    bubble_up(p, heap)
def merge(heap1, heap2):
    merged_heap = heap1 + heap2
    heapify(merged_heap)
    return merged_heap
def bubble_up(index, heap):
    parent = (index - 1) // 2
    while index > 0 and heap[index] < heap[parent]:
        heap[index], heap[parent] = heap[parent], heap[index]
        index = parent
        parent = (index - 1) // 2
def bubble_down(index, heap):
    left_child = 2 * index + 1
    right_child = 2 * index + 2
    smallest = index
    if left_child < len(heap) and heap[left_child] < heap[smallest]:
        smallest = left_child
    if right_child < len(heap) and heap[right_child] < heap[smallest]:
        smallest = right_child
    if smallest != index:
        heap[index], heap[smallest] = heap[smallest], heap[index]
        bubble_down(smallest, heap)
def heapify(heap):
    n = len(heap)
    for i in range((n // 2) - 1, -1, -1):
        bubble_down(i, heap)