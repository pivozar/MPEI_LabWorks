using System;

class MyId {
    public string Name;
    public int Attribute;
    
    public MyId(string name, int value) {
        Name = name;
        Attribute = value;
    }

    public static bool operator < (MyId lhs, MyId rhs) {
        return string.Compare(lhs.Name, rhs.Name) < 0;
    }
    public static bool operator > (MyId lhs, MyId rhs) {
        return string.Compare(lhs.Name, rhs.Name) > 0;
    }
    public static bool operator == (MyId lhs, MyId rhs) {
        return lhs.Name == rhs.Name;
    }
    public static bool operator != (MyId lhs, MyId rhs) {
        return lhs.Name != rhs.Name;
    }
}

class IdTable {
    private MyId[] table;
    private int length;
    public int size;
    public IdTable() {
        table = new MyId[2];
        size = 0;
        length = 2;
    }
    public void PrintTable() {
        Console.Write("[ ");
        for (int i = 0; i < size; i++)
            Console.Write("{" + table[i].Name + ":" + table[i].Attribute + "}, ");
        Console.WriteLine("]");
    }
    public void Add(MyId new_id) {
        if (size + 1 == length) {
            Resize(2 * length);
        }
        if (size == 0) {
            table[0] = new_id;
            size++;
        }
        else {
            int i = Find(new_id.Name);
            if (i == size) {
                table[size] = new_id;
                size++;
            }
            else if (table[i].Name == new_id.Name)
                table[i].Attribute = new_id.Attribute;
            else if (i < size) {
                for (int j = size; j != i; j--)
                    table[j] = table[j - 1];
                table[i] = new_id;
                size++;
            }
        }
    }
    public bool Remove(string key) {
        if (size == 0)
            return false;
        int i = Find(key);
        if (table[i].Name != key)
            return false;
        if (i == size - 1)
            size--;
        else {
            for (int j = i; j < size-1; ++j) {
                table[j] = table[j + 1];
            }
            size--;
        }
        if (size < length / 2)
            Resize(length / 2);
        return true;
    }
    private void Resize(int new_length) {
        MyId[] new_data = new MyId[new_length];
        for (int i = 0; i < size; i++) {
            new_data[i] = table[i];
        }
        table = new_data;
        length = new_length;
    }
    public int Get(string key) {
        int i = Find(key);
        if (i == size) return 0;
        MyId res = table[i];
        if (res.Name == key)
            return res.Attribute;
        return 0;
    }
    private int Find(string key) {
        int left = 0;
        int right = size;
        int mid = (left + right) / 2;
        while (left + 1 < right) {
            mid = (left + right) / 2;
            if (key.CompareTo(table[mid].Name) < 0)
                right = mid;
            else
                left = mid;
        }
        if (key == table[left].Name)
            return left;
        else
            return left + 1;
    }
}
class Program {
    static void StartDialoge(IdTable t) {
        Console.WriteLine("Enter one of the following commands:");
        Console.WriteLine("0 - Exit\n" +
                          "1 - Add Identificator\n" +
                          "2 - Remove Iddentificator\n" +
                          "3 - Get Id's attribute by name\n" +
                          "4 - Print table\n");
        int cmd = 1;
        string id_name = "";
        int value = 0;
        while (cmd != 0) {
            Console.Write("Enter the command: ");
            cmd = Convert.ToInt32(Console.ReadLine());
            if (cmd == 1) {
                Console.WriteLine("Enter Id's name and then value on 2 lines");
                id_name = Console.ReadLine();
                value = Convert.ToInt32(Console.ReadLine());
                t.Add(new MyId(id_name, value));
            }
            else if (cmd == 2) {
                Console.WriteLine("Enter Id's name to delete");
                id_name = Console.ReadLine();
                if (t.Remove(id_name))
                    Console.WriteLine($"{id_name} deleted successfully");
                else
                    Console.WriteLine("There's no such id.");
            }
            else if (cmd == 3) {
                Console.WriteLine("Enter Id's name");
                id_name = Console.ReadLine();
                Console.WriteLine($"{id_name} - {t.Get(id_name)}");
            }
            else if (cmd == 4) t.PrintTable();
            else if (cmd != 0) Console.WriteLine("An unknown command. Please, try again.");
        }
    }
    static void Main() {
        IdTable t = new IdTable();
        string[] names = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
        for (int i=0; i<10; ++i) {
            t.Add(new MyId(names[i], i));
        }
        StartDialoge(t);
    }
}