using System;
/*
 Множество целых чисел на основе массива (вклю-чение, исключение элемента, поиск, объединение множеств)
*/

class Set {
    private int[] _data;
    private int length;
    public int size;

    public Set() {
        _data = new int[2];
        size = 0;
        length = 2;
    }
    public Set(int[] arr, int new_size) {
        _data = new int[new_size * 2];
        size = new_size;
        length = new_size * 2;
        for (int i=0; i<new_size; i++) {
            _data[i] = arr[i];
        }
    }
    private void Resize(int new_length) {
        int[] new_data = new int[new_length];
        for (int i=0; i < size; i++) {
            new_data[i] = _data[i];
        }
        _data = new_data;
        length = new_length;
    }
    public void Add(int elem) {
        if (Find(elem) == -1) {
            if (length - size == 1)
                Resize(length * 2);
            _data[size] = elem;
            size++;
        }
    }
    public void PrintSet() {
        Console.Write("{ ");
        for (int i=0; i < size; i++)
            Console.Write(_data[i] + ", ");
        Console.WriteLine("}");
    }
    private int Find(int key) {
        int i = 0;
        while (i < size && _data[i] != key)
            i++;
        if (i == size) return -1;
        else return i;
    }
    public bool Exists(int key) {
        return (Find(key) != -1);
    }
    public void Remove(int key) {
        int index = Find(key);
        if (index == -1) return;
        for (int i=index; i < size; i++)
            _data[i] = _data[i + 1];
        _data[size - 1] = 0;
        size--;
        if (size < length / 2)
            Resize(length / 2);
    }
    public int this[int i] {
        get {
            if (i >= 0 && i < size) return _data[i];
            else return 0;
        }
    }
    public Set Union(Set s) {
        Set res = new Set();
        for (int i=0; i<size; i++)
            res.Add(_data[i]);
        for (int i=0; i<s.size; i++)
            res.Add(s[i]);
        return res;
    }
}

class Program {
    static void Main(string[] args) {
        int[] arr1 = { 1, 2, 3 };
        int[] arr2 = { 2, 3, 4 };
        Set s1 = new Set(arr1, 3);
        Set s2 = new Set(arr2, 3);
        Set res = s1.Union(s2);
        s1.Add(5);
        s2.Remove(3);
        s1.PrintSet();
        s2.PrintSet();
    }
}