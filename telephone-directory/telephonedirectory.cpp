#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

class Entry
{
    private:
        string name;
        string address;
        string phone_number;

    public:
        Entry();
        Entry(string n, string addy, string phone);

        void setName(string name);
        void setAddress(string address);
        void setPhoneNumber(string phone_number1);
        string getName();
        string getAddress();
        string getPhoneNumber();

        friend ostream& operator<<(ostream& os, const Entry& source);
        friend istream& operator>>(istream &in, Entry &source);
        bool operator==(const Entry &rhs);
};
// Default Constructor
Entry::Entry()
{
    name="";
    address="";
    phone_number="";
}
// Parameterized Constructor
Entry::Entry(string n, string addy, string phone)
{
    name = n;
    address = addy;
    phone_number = phone;
}
// Setter for name
void Entry::setName(string name1)
{
    name = name1;
}
// Setter for address
void Entry::setAddress(string address1)
{
    address = address1;
}
// Setter for phone number
void Entry::setPhoneNumber(string phone_number1)
{
    phone_number = phone_number1;
}
// Getter for name
string Entry::getName()
{
    return name;
}
// Getter for Address
string Entry::getAddress()
{
    return address;
}
// Getter for phone number
string Entry::getPhoneNumber()
{
    return phone_number;
}
// << operator to output entries 
ostream& operator<<(ostream& out, const Entry& source)
{
    out << "Name: " << source.name << endl;
    out << "Address: " << source.address << endl;
    out << "Phone: " << source.phone_number << endl;
    return out;
}
// >> operator to input entries
istream& operator>>(istream &in, Entry &source)
{
    bool flag = true;
    cout << "Input the name: " << endl;
    cin.clear();
    cin.ignore(10000,'\n');
    getline(in,source.name);
    cout << "Input the address: " << endl;
    cin.clear();
    getline(in,source.address);
    cout << "Input the phone number: " << endl;
    while(flag==true)
    {
        in >> source.phone_number;
        if (source.phone_number.length()!=11)
        {
            cout << "The length of the phone number is not 11!" << endl;
            flag = true;
        }
        else if(source.phone_number.substr(0,2) != "03")
        {
            cout << "The phone number does not start with 03!" << endl;
            flag = true;
        }
        else
        {
            flag = false;
        }
    }
    return in;
}
// == operator to compare entries
bool Entry::operator==(const Entry &rhs)
{
    if(phone_number == rhs.phone_number)
    {
        return true;
    }
    else
    {
        return false;
    }
}

class Directory
{
    private:
        Entry *entry;
        int entries_made;

    public:
        Directory();
        Directory(Entry *entry1, int e);
        ~Directory();

        void addEntry();
        void removeEntry(string phone_num);
        void lookup(string name);
        void lookupPrefix (string prefix);
        void lookupCity (string city);

        friend ostream& operator<<(ostream& out, const Directory& source);
        void sortAscending ();
        Directory operator+(const Directory &rhs);

        void saveDirectory();
        void loadDirectory();
};
// Default Constructor 
Directory::Directory()
{
    entries_made = 0;
    entry = NULL;
}
// Parameterized constructor 
Directory::Directory(Entry *entry1, int e)
{
    entries_made = e;
    entry = new Entry[entries_made];
    for(int i=0; i<e;i++)
    {
        entry[i]=entry1[i];
    }
}
// Destructor for entry
Directory::~Directory()
{
    delete [] entry;
}
// Add entry function to add an entry
void Directory::addEntry()
{
    cout <<"Please input the new entry!" << endl;
    Entry new_entry;
    cin >> new_entry; //prompting user for entry details
    for(int i=0;i<entries_made;i++) //checking if phone number is already in directory
    {
        if(entry[i].getPhoneNumber()==new_entry.getPhoneNumber())
        {
            cout << "Phone number " << new_entry.getPhoneNumber() << " already exists." << endl;
            return;
        }
    }

    Entry* new_entries = new Entry[entries_made + 1];
    for (int i = 0; i < entries_made; ++i) 
    {
        new_entries[i] = entry[i];
    }
    new_entries[entries_made]=new_entry;
    delete[] entry;
    entry = new_entries;
    entries_made++;
    cout << "Entry added successfully!" << endl;
}
// Remove entry function to remove an entry
void Directory::removeEntry(string phone_num)
{
    bool flagx =true;
    for (int i = 0; i < entries_made; i++) 
    {
        if(entry[i].getPhoneNumber() == phone_num) 
        {
            flagx=false;
            for (int j = i; j < entries_made - 1; j++) 
            {
                entry[j] = entry[j + 1];
            }
            entries_made--;
            cout << "Entry with phone number " << phone_num << " removed." << endl;
        }
    }
    if(flagx == true)
    {
        cout << "Entry with phone number " << phone_num << " not found." << endl;
    }
}
// Look up function to look for entries with the same name
void Directory::lookup(string name1)
{
    bool sfound = true;
    for(int i = 0; i < entries_made; i++)
    {
        if(entry[i].getName() == name1)
        {
            cout << entry[i] << endl;
            sfound = false;
        }
    }
    if(sfound==true)
    {
        cout << "No entries found with the name '" << name1 << "'." << endl;
    }
}
// Look up prefix function to search for entries that have the same prefix
void Directory::lookupPrefix(string prefix)
{
    bool pfound = false; 
    for (int i = 0; i < entries_made; i++)
    {
        const string phoneNumber = entry[i].getPhoneNumber();
        bool flagy = true; 
        for (int j = 0; j < prefix.length(); j++)
        {
            if (prefix[j] != phoneNumber[j])
            {
                flagy = false;
                break;
            }
        }
        if (flagy==true)
        {
            cout << entry[i] << endl;
            pfound = true;
        }
    }
    if (!pfound)
    {
        cout << "No entries found with the prefix '" << prefix << "' in the directory." << endl;
    }
}
// Look up city function used to search for entries using the name of the city
void Directory::lookupCity(string city)
{
    bool cfound = true;
    for(int i=0;i < entries_made;i++)
    {
        string address = entry[i].getAddress();
        int alength = address.length();
        int index=0;
        for(int i =address.length();i>0;i--)
        {
            if(address.substr(i,1) == " ")
            {
                index = i;
                break;
            }
        }
        string lower_city = city;
        for(int i =0;i<city.length();i++)
        {
            lower_city[i] = tolower(city[i]);
        }
        string compare = address.substr(index+1,address.length()-index);
        string compare_lower = compare;
        for(int i =0;i<compare.length();i++)
        {
            compare_lower[i] = tolower(compare[i]);
        }
        if(compare == city || compare_lower == lower_city)
        {
            cout << entry[i] << endl;
            cfound = false;
        }
    }
    if(cfound==true)
    {
        cout << "No entries found with the city name '" << city << "' in the directory." << endl;
    }
}
// << operator to output the directory
ostream& operator<<(ostream& out, const Directory& source)
{
    out << "Directory Entries:" << endl;
    for (int i = 0; i < source.entries_made; ++i) 
    {
        out << source.entry[i] << endl;
    }
    return out;
}
// Sort Ascending function to sort all entries in order
void Directory::sortAscending()
{
    bool complete = true;
    while(complete==true)
    {
        for (int i = 0; i < entries_made - 1; i++) 
        {
            if (entry[i].getName() > entry[i + 1].getName()) 
            {
                Entry temp = entry[i];
                entry[i] = entry[i + 1];
                entry[i + 1] = temp;
            }
        }
        complete = false;
    }
}  
// + operator to add two directories
Directory Directory::operator+(const Directory &rhs)  
{
    int temp = entries_made;
    int size = rhs.entries_made + entries_made;
    Entry* combined = new Entry [size];
    for (int i = 0; i < entries_made; i++) 
    {
        combined[i] = entry[i];
    }
    for (int i = 0; i < rhs.entries_made; i++) 
    {
        bool duplicateFlag = false;

        for (int j = 0; j < size; j++) 
        {
            if (combined[j] == rhs.entry[i]) 
            {
                duplicateFlag = true;
                size--;
            }
        }

        if (duplicateFlag == false) 
        {
            combined[temp] = rhs.entry[i];
            temp++;
        }
    }
    Directory comb(combined,size);
    delete [] combined;
    return comb;
}
// Save Directory Function to save the current objects
void Directory::saveDirectory()
{
        ofstream file("directory.txt");
        if (file.is_open()) 
        {
            for (int i = 0; i < entries_made; i++) {
                file << entry[i].getName()<<endl;
                file <<  entry[i].getAddress()<<endl;
                file << entry[i].getPhoneNumber()<<endl;
            }
            cout << "Directory saved successfully." << endl;
            file.close();
        } 
        else 
        {
            cout << "Failed to save directory." << endl;
        }
}
// Load Directory function to load the previously saved directory
void Directory::loadDirectory()
{
    ifstream file("directory.txt");
    if (file.is_open())
    {
        string name, address, phoneNumber;
        while (getline(file, name) && getline(file, address) && getline(file, phoneNumber))
        {
            Entry new_entry(name, address, phoneNumber);          
            Entry* new_entries = new Entry[entries_made + 1];
            for (int i = 0; i < entries_made; i++) 
            {
                new_entries[i] = entry[i];
            }
            delete[] entry;
            entry = new_entries;
            entry[entries_made] = new_entry;
            ++entries_made;
        }

        cout << "Directory loaded successfully." << endl;
        file.close();
    }
    else
    {
        cout << "Failed to load directory." << endl;
    }
}

// Helper function to display the main menu
void displayMainMenu() 
{
    cout << "--- Telephone Directory ---" << endl;
    cout << "A) Create a new directory" << endl;
    cout << "B) Load saved directory" << endl;
}
// Helper function to display the sub-menu for directory operations
void displayDirectoryMenu() 
{
    cout << "Select the appropriate option (A-G) to perform an operation: " << endl;
    cout << "A) Make an entry" << endl;
    cout << "B) Remove an entry" << endl;
    cout << "C) Lookup based on name" << endl;
    cout << "D) Lookup based on prefix" << endl;
    cout << "E) Lookup based on city" << endl;
    cout << "F) Save directory" << endl;
    cout << "G) Exit" << endl;
    cout << "H) Create Second Directory/Add Directories" << endl;
}
// Helper function to handle directory operations and make int main more concise
void handleDirectoryOperations(Directory& dir,Directory& dir2) 
{
    bool m2flag = true;
    while (m2flag) 
    {
        char com;
        displayDirectoryMenu();
        cin >> com;
        switch (com) 
        {
            case 'A':
            {
                dir.addEntry();
                cout << endl;
                dir.sortAscending();
                cout << dir;
                break;
            }
            case 'B':
            {
                string p;
                cout << "Please provide the phone number you would like to remove" << endl;
                cin >> p;
                dir.removeEntry(p);
                cout << endl;
                dir.sortAscending();
                cout << dir;
                break;
            }
            case 'C':
            {
                string n;
                cout << "Please provide the name you would like to look up" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                getline(cin, n);
                dir.lookup(n);
                break;
            }
            case 'D':
            {
                string prefix;
                cout << "Please provide the prefix you would like to look up" << endl;
                cin >> prefix;
                dir.lookupPrefix(prefix);
                break;
            }
            case 'E':
            {
                string c;
                cout << "Please provide the city name you would like to look up" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                cin >> c;
                dir.lookupCity(c);
                break;
            }
            case 'F':
            {
                dir.saveDirectory();
                break;
            }
            case 'G':
            {
                cout << "Exiting Program" << endl;
                exit(0);
            }
            case 'H':
            {
                bool flagx = true;
                while (flagx) 
                {
                    char com1;
                    cout << "--- Telephone Directory ---" << endl;
                    cout << "Select the appropriate option (A-D) to perform an operation: " << endl;
                    cout << "A) Make an entry in directory B" << endl;
                    cout << "B) Remove an entry in directory B" << endl;
                    cout << "C) Add both directories" << endl;
                    cout << "D) Exit" << endl;
                    cin >> com1;
                    switch (com1) 
                    {
                        case 'A':
                        {
                            dir2.addEntry();
                            cout << endl;
                            dir2.sortAscending();
                            cout << dir2;
                            break;
                        }
                        case 'B':
                        {
                            string p;
                            cout << "Please provide the phone number you would like to remove" << endl;
                            cin >> p;
                            dir2.removeEntry(p);
                            cout << endl;
                            dir2.sortAscending();
                            cout << dir2;
                            break;
                        }
                        case 'C':
                        {
                            cout << dir2 + dir;
                            break;
                        }
                        case 'D':
                        {
                            flagx = false;
                            break;
                        }
                        default:
                        {
                            cout << "Invalid input" << endl;
                            m2flag = true;
                        }
                    }
                }
                break;
            }
            default:
            {
                cout << "Invalid input" << endl;
                m2flag = true;
            }
        }
    }
}
// int main
int main() 
{
    Directory dir;
    Directory dir2;
    bool mflag = true;
    while (mflag) 
    {
        char command;
        displayMainMenu();
        cin >> command;
        switch (command) 
        {
            case 'A':
                handleDirectoryOperations(dir,dir2);
                break;
            case 'B':
                dir.loadDirectory();
                handleDirectoryOperations(dir,dir2);
                break;
            default:
                cout << "Invalid input!" << endl;
                mflag = true;
        }
    }
    return 0;
}