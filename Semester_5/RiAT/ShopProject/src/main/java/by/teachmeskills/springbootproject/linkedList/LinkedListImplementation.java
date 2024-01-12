package by.teachmeskills.springbootproject.linkedList;

import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;

import java.util.Collection;

public class LinkedListImplementation<T> {
    private int size;
    private Node<T> head;
    private Node<T> tail;

    public LinkedListImplementation() {
        clear();
    }

    public LinkedListImplementation(Collection<? extends T> c) {
        clear();
        for (T elem : c) {
            add(elem);
        }
    }

    @AllArgsConstructor
    @NoArgsConstructor
    private static class Node<T> {
        private T info;
        private Node<T> next;
        private Node<T> prev;
    }

    private void addAfterNode(Node<T> node, T elem) {
        Node<T> newNode = new Node<>(elem, node.next, node);
        node.next.prev = newNode;
        node.next = newNode;
    }

    private void addBeforeNode(Node<T> node, T elem) {
        Node<T> newNode = new Node<>(elem, node, node.prev);
        node.prev.next = newNode;
        node.prev = newNode;
    }

    private void removeNode(Node<T> node) {
        node.prev.next = node.next;
        node.next.prev = node.prev;
    }

    private Node<T> getNode(int index, int topBorder) {
        if (index > topBorder || index < 0) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds");
        }
        Node<T> current;
        if (size - index > index) {
            current = head;
            for (int i = 0; i <= index; ++i) {
                current = current.next;
            }
        } else {
            current = tail;
            for (int i = size; i > index; --i) {
                current = current.prev;
            }
        }
        return current;
    }

    private int getIndexOfElem(T elem, boolean isFirstIndex) {
        Node<T> current;
        if (isFirstIndex) {
            current = head.next;
            for (int i = 0; i < size; ++i) {
                if (current.info.equals(elem)) {
                    return i;
                }
                current = current.next;
            }
        } else {
            current = tail.prev;
            for (int i = size - 1; i >= 0; --i) {
                if (current.info.equals(elem)) {
                    return i;
                }
                current = current.prev;
            }
        }
        return -1;
    }

    public void add(int index, T elem) {
        Node<T> node = getNode(index, size);
        addBeforeNode(node, elem);
        ++size;
    }

    public void add(T elem) {
        add(size, elem);
    }

    public T remove(int index) {
        Node<T> result = getNode(index, size - 1);
        removeNode(result);
        --size;
        return result.info;
    }

    public boolean remove(T elem) {
        int index = getIndexOfElem(elem, true);
        if (index != -1) {
            removeNode(getNode(index, size - 1));
            --size;
        }
        return index != -1;
    }

    public T get(int index) {
        return getNode(index, size - 1).info;
    }

    public boolean contains(T elem) {
        return getIndexOfElem(elem, true) != -1;
    }

    public void clear() {
        size = 0;
        tail = new Node<>();
        head = new Node<>(null, tail, null);
        tail.prev = head;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public int indexOf(T elem) {
        return getIndexOfElem(elem, true);
    }

    public int lastIndexOf(T elem) {
        return getIndexOfElem(elem, false);
    }

    public void addAll(Collection<? extends T> c) {
        for (T elem : c) {
            add(elem);
        }
    }

    public void retainAll(Collection<? extends T> c) {
        Node<T> current = head.next;
        int initialSize = size;
        for (int i = 0; i < initialSize; ++i) {
            if (!c.contains(current.info)) {
                removeNode(current);
                --size;
            }
            current = current.next;
        }
    }

    public void removeAll(Collection<? extends T> c) {
        Node<T> current = head.next;
        int initialSize = size;
        for (int i = 0; i < initialSize; ++i) {
            if (c.contains(current.info)) {
                removeNode(current);
                --size;
            }
            current = current.next;
        }
    }

    public Object[] toArray() {
        Object[] array = new Object[size];
        Node<T> current = head.next;
        for (int i = 0; i < size; ++i) {
            array[i] = current.info;
            current = current.next;
        }
        return array;
    }

    @Override
    public String toString() {
        Node<T> node = head.next;
        StringBuilder result = new StringBuilder("[");
        if (node.info != null) {
            result.append(node.info);
            node = node.next;
        }
        if (node != null) {
            while (!node.equals(tail)) {
                result.append(", ").append(node.info);
                node = node.next;
            }
        }
        result.append("]");
        return result.toString();
    }


}
