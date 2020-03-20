'''
Author:    Eric Westfall
Date:      4/14/2018
File:      LinkedList.py (exercises: 18-2.py, linkList1.py, linkList2.py)
Purpose:   Implement addAll(otherList), removeAll(otherList), retainAll(otherList)
           for 18.1/linkList1.
           Implement clear(), contains(Object o), get(int index)
           and indexOf(Object o) for 18.2.
           Implement remove(e), lastIndexOf(Object o), set(int index, Object o)
           for 18.3/linkList2.
'''


class LinkedList:
    def __init__(self):
        self.__head = None
        self.__tail = None
        self.__size = 0

    # Return the head element in the list 
    def getFirst(self):
        if self.__size == 0:
            return None
        else:
            return self.__head.element
    
    # Return the last element in the list 
    def getLast(self):
        if self.__size == 0:
            return None
        else:
            return self.__tail.element

    # Add an element to the beginning of the list 
    def addFirst(self, e):
        newNode = Node(e) # Create a new node
        newNode.next = self.__head # link the new node with the head
        self.__head = newNode # head points to the new node
        self.__size += 1 # Increase list size

        if self.__tail == None: # the new node is the only node in list
            self.__tail = self.__head

    # Add an element to the end of the list 
    def addLast(self, e):
        newNode = Node(e) # Create a new node for e
    
        if self.__tail == None:
            self.__head = self.__tail = newNode # The only node in list
        else:
            self.__tail.next = newNode # Link the new with the last node
            self.__tail = self.__tail.next # tail now points to the last node
    
        self.__size += 1 # Increase size

    # Same as addLast 
    def add(self, e):
        self.addLast(e)

    # Insert a new element at the specified index in this list
    # The index of the head element is 0 
    def insert(self, index, e):
        if index == 0:
            self.addFirst(e) # Insert first
        elif index >= self.__size:
            self.addLast(e) # Insert last
        else: # Insert in the middle
            current = self.__head
            for i in range(1, index):
                current = current.next
            temp = current.next
            current.next = Node(e)
            (current.next).next = temp
            self.__size += 1

    # Remove the head node and
    #  return the object that is contained in the removed node. 
    def removeFirst(self):
        if self.__size == 0:
            return None # Nothing to delete
        else:
            temp = self.__head # Keep the first node temporarily
            self.__head = self.__head.next # Move head to point the next node
            self.__size -= 1 # Reduce size by 1
            if self.__head == None: 
                self.__tail = None # List becomes empty 
            return temp.element # Return the deleted element

    # Remove the last node and
    # return the object that is contained in the removed node
    def removeLast(self):
        if self.__size == 0:
            return None # Nothing to remove
        elif self.__size == 1: # Only one element in the list
            temp = self.__head
            self.__head = self.__tail = None  # list becomes empty
            self.__size = 0
            return temp.element
        else:
            current = self.__head
        
            for i in range(self.__size - 2):
                current = current.next
        
            temp = self.__tail
            self.__tail = current
            self.__tail.next = None
            self.__size -= 1
            return temp.element

    # Remove the element at the specified position in this list.
    #  Return the element that was removed from the list. 
    def removeAt(self, index):
        if index < 0 or index >= self.__size:
            return None # Out of range
        elif index == 0:
            return self.removeFirst() # Remove first 
        elif index == self.__size - 1:
            return self.removeLast() # Remove last
        else:
            previous = self.__head
    
            for i in range(1, index):
                previous = previous.next
        
            current = previous.next
            previous.next = current.next
            self.__size -= 1
            return current.element

    # Return true if the list is empty
    def isEmpty(self):
        return self.__size == 0
    
    # Return the size of the list
    def getSize(self):
        return self.__size

    def __str__(self):
        result = "["

        current = self.__head
        for i in range(self.__size):
            result += str(current.element)
            current = current.next
            if current != None:
                result += ", " # Separate two elements with a comma
            else:
                result += "]" # Insert the closing ] in the string

        return result

    # Clear the list */
    def clear(self):
        self.__size = 0
        self.__head = self.__tail = None

    # Return true if this list contains the element o
    #since the linked list is unsorted, this is a linear search with O(n) time.
    def contains(self, e):
        node = self.__head
        for _ in range(self.__size - 1):
            if e == node.element:
                return True
            node = node.next   
        return False

    # Remove the element and return true if the element is in the list
    #since the assignment is unclear, this function removes all instances of the element
    #and not just the first instance
    def remove(self, e):
        node = self.__head
        flag = False
        for _ in range(self.__size):
            if e == node.element:
                if node == self.__head:
                    self.removeFirst()
                else:
                    previousNode.next = node.next
                    self.__size -= 1
                flag = True
                if node == self.__tail:
                    return flag
                node = node.next
            else:
                previousNode = node
                if node == self.__tail:
                    return flag
                node = node.next
        return flag

    # Return the element from this list at the specified index 
    def get(self, index):
        if index < 0 or index >= self.__size:
            return None # Out of range
        node = self.__head
        if index == 0:
            return node.element
        for _ in range(index - 1):
            node = node.next
        return node.element

    # Return the index of the head matching element in this list.
    # Return -1 if no match.
    #an unordered list gets a linear search O(n)
    def indexOf(self, e):
        node = self.__head
        for index in range(self.__size):
            if node.element == e:
                return index
            node = node.next
        return -1

    # Return the index of the last matching element in this list
    #  Return -1 if no match.
    #an unordered list gets a linear search O(n) - I really wish I could implement something else xD
    def lastIndexOf(self, e):
        node = self.__head
        returnIndex = -1
        for index in range(self.__size):
            if node.element == e:
                returnIndex = index
            node = node.next
        return returnIndex

    # Replace the element at the specified position in this list
    #  with the specified element. */
    def set(self, index, e):
        if index < 0 or index >= self.__size:
            return None # Out of range
        elif index == 0: #replace first element
            self.removeFirst(); self.setFirst(e)
            return None
        elif index == self.__size - 1: #replace last element
            self.removeLast(); self.setLast(e)
            return None
        self.removeAt(index)
        self.insert(index, e)
        return None

    #Unions the lists
    def addAll(self, otherList):
        flag = False
        for element in otherList:
            if self.contains(element) != True:
                self.addFirst(element)
                flag = True
        return flag

    #Set difference self - otherList
    def removeAll(self, otherList):
        node = self.__head
        flag = False
        for _ in range(self.__size):
            if node.element in otherList:
                self.remove(node.element)
                flag = True
            if node == self.__tail:
                return flag
            node = node.next
        return flag

    #Set intersection
    def retainAll(self, otherList):
        node = self.__head
        flag = False
        for _ in range(self.__size):
            if node.element not in otherList:
                self.remove(node.element)
                flag = True
            if node == self.__tail:
                return flag
            node = node.next
        return flag
    
    # Return elements via indexer
    def __getitem__(self, index):
        return self.get(index)

    # Return an iterator for a linked list
    def __iter__(self):
        return LinkedListIterator(self.__head)
    
# The Node class
class Node:
    def __init__(self, element):
        self.element = element
        self.next = None

class LinkedListIterator: 
    def __init__(self, head):
        self.current = head
        
    def __next__(self):
        if self.current == None:
            raise StopIteration
        else:
            element = self.current.element
            self.current = self.current.next
            return element    
        
