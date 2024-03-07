// FitnessClub - Your Ultimate Fitness Solution
#include<fstream>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

class AdminLogin
{
	string adminCode;
public:
	int authenticateAdmin()
	{
		cout << "Enter the admin code: ";
		cin >> adminCode;
		if(adminCode == "admin123")
		{
			int result = getAdminPassword();
			if (result == 1)
			{
				cout << "Login successful!" << endl;
				return 1;
			}
		}
		else
		{
			cout << "Username not found" << endl;
			authenticateAdmin();
			cout << "Login failed" << endl;
			return 0;
		}
	}

	int getAdminPassword();
};

int AdminLogin::getAdminPassword()
{
	string password;
	cout << "Enter the password: ";
	cin >> password;
	if(password == "fitClubAdmin")
	{
		cout << "WELCOME!!" << endl;
		return 1;
	}
	else
	{
		cout << "Entered password is incorrect" << endl;
		getAdminPassword();
		return 0;
	}
}

void goldClassAllotment(int goldCount, int silverCount)
{
	if(goldCount != 0)
	{
		cout << goldCount << endl;
		cout << "Trainer allotted for Gold Class\n";
	}
	else
	{
		cout << "No trainer available\n";
	}
}

void silverClassAllotment(int goldCount, int silverCount)
{
	if(silverCount != 0)
	{
		cout << silverCount << endl;
		cout << "Trainer allotted for Silver Class\n";
	}
	else
	{
		cout << "\nNo trainer available\n";
		if(goldCount != 0)
		{
			cout << "Enter another class\n";
			goldClassAllotment(goldCount, silverCount);
		}
	}
}

int traineeAllotment(char* classType)
{
	char chosenClass[10];
	int i, goldClassCount = 3, silverClassCount = 5;
	strcpy(chosenClass, classType);

	if((goldClassCount != 0) || (silverClassCount != 0))
	{
		if(strcmp(chosenClass, "gold") == 0)
		{
			goldClassCount--;
			goldClassAllotment(goldClassCount, silverClassCount);
		}
		else if(strcmp(chosenClass, "silver") == 0)
		{
			silverClassCount--;
			silverClassAllotment(goldClassCount, silverClassCount);
		}
	}
	else
	{
		cout << "No trainer available\n";
		return 1;
	}
}

class FitnessMember
{
	int memberNumber;
	char memberName[50], membershipClass[50], preferredTimings[50];
	float membershipFee;
	long int contactNumber;
public:
	int chooseTimeSlots()
	{
		int chosenSlot;
		cout << "Please select your preferred timings\nPress 1 for: Morning 6-7\nPress 2 for: Morning 7-8\nPress 3 for: Morning 8-9\n";
		cout << "Press 4 for: Evening 4-5\nPress 5 for: Evening 5-6\nPress 6 for: Evening 6-7\n";
		cin >> chosenSlot;

		switch(chosenSlot)
		{
			case 1: strcpy(preferredTimings, "6AM-7AM"); break;
			case 2: strcpy(preferredTimings, "7AM-8AM"); break;
			case 3: strcpy(preferredTimings, "8AM-9AM"); break;
			case 4: strcpy(preferredTimings, "4PM-5PM"); break;
			case 5: strcpy(preferredTimings, "5PM-6PM"); break;
			case 6: strcpy(preferredTimings, "6PM-7PM"); break;
		}
	}

	void createMember()
	{
		int chosenClass, allocationResult;
		cout << endl << "Please Enter The Member Number: ";
		cin >> memberNumber;
		cout << endl << "Please Enter The Name of The Member: ";
		getchar();
		cin.getline(memberName ,50);
		cout << endl << "Please Enter The Contact Number: ";
		cin >> contactNumber;
		cout << "1. Gold Class\n2. Silver Class\n";
		cout << "Enter the choice: ";
		cin >> chosenClass;

		switch (chosenClass)
		{
			case 1: 
				{
					strcpy(membershipClass, "gold");
					membershipFee = 2500;
					cout << "Your monthly fee would be: " << membershipFee << endl;
					allocationResult = traineeAllotment(membershipClass);
				}
				break;
			case 2: 
				{
					strcpy(membershipClass, "silver");
					membershipFee = 2000;
					cout << "Your monthly fee would be: " << membershipFee << endl;
					allocationResult = traineeAllotment(membershipClass);
				}
				break;
		}
		chooseTimeSlots();
	}

	void displayMember()
	{
		cout << endl << "Member Code: " << memberNumber;
		cout << endl << "Name: " << memberName;
		cout << endl << "Category: " << membershipClass;
		cout << endl << "Fee: " << membershipFee;
		cout << endl << "Contact: " << contactNumber;
		cout << endl << "Timings: " << preferredTimings << endl;
	}

	int getMemberNumber()
	{
		return memberNumber;
	}

	float getMembershipFee()
	{
		return membershipFee;
	}

	char* getMemberName()
	{
		return memberName;
	}

	float getContactNumber()
	{
		return contactNumber;
	}
};

fstream fitnessFile;
FitnessMember member1;

void saveFitnessMember()
{
    fitnessFile.open("fitnessData.dat", ios::out|ios::app);
    member1.createMember();
    fitnessFile.write((char*)&member1, sizeof(member1));
    fitnessFile.close();
    cout << endl << endl << "The member has been successfully added...";
    getchar();
}

void showAllMembers()
{
    system("cls");
    cout << endl << "\t\tRECORDS...";
    fitnessFile.open("fitnessData.dat", ios::in);
    while(fitnessFile.read((char*)&member1, sizeof(member1)))
    {
    	member1.displayMember();
    	getchar();
    }
    fitnessFile.close();
}

void displayFitnessRecord(int number)
{
    bool found = false;
	fitnessFile.open("fitnessData.dat", ios::in);
    while(fitnessFile.read((char*)&member1, sizeof(member1)))
    {
    	if(member1.getMemberNumber() == number)
    	{
    		system("cls");
    		member1.displayMember();
    		found = true;
    	}
    }
    fitnessFile.close();
    if(!found)
    cout << "\n\nNo record found";
    getchar();
}

void editFitnessMember()
{
    int number;
    bool found = false;
    system("cls");
    cout << endl << endl << "\tPlease Enter The Member Number: ";
    cin >> number;
    fitnessFile.open("fitnessData.dat", ios::in|ios::out);
    while(fitnessFile.read((char*)&member1, sizeof(member1)) && !found)
    {
    	if(member1.getMemberNumber() == number)
    	{
    		member1.displayMember();
    		cout << "\nPlease Enter The New details of the member: " << endl;
    		member1.createMember();
    		int position = 1 * sizeof(member1);
    		fitnessFile.seekp(position, ios::cur);
    		fitnessFile.write((char*)&member1, sizeof(member1));
    		cout << endl << endl << "\t Record Successfully Updated...";
    		found = true;
    	}
    }
    fitnessFile.close();
    if(!found)
    {
    	cout << endl << endl << "Record Not Found...";
    	getchar();
    }
}

void deleteFitnessMember()
{
    int number;
    system("cls");
    cout << endl << endl << "Please Enter The Member Number: ";
    cin >> number;
    fitnessFile.open("fitnessData.dat", ios::in|ios::out);
    fstream tempFile;
    tempFile.open("TempData.dat", ios::out);
    fitnessFile.seekg(0, ios::beg);
    while(fitnessFile.read((char*)&member1, sizeof(member1)))
    {
    	if(member1.getMemberNumber() != number)
    	{
    		tempFile.write((char*)&member1, sizeof(member1));
    	}
    }
    tempFile.close();
    fitnessFile.close();
    remove("fitnessData.dat");
    rename("TempData.dat", "fitnessData.dat");
    cout << endl << endl << "\tRecord Deleted...";
    getchar();
}

void fitnessManagement()
{
    for(;;)
    {
        system("cls");
        int option;
        cout << "\t***********************************************";
        cout << "\n\tPress 1 to CREATE MEMBER";
        cout << "\n\tPress 2 to DISPLAY ALL RECORDS";
        cout << "\n\tPress 3 to SEARCH FOR A PARTICULAR RECORD ";
        cout << "\n\tPress 4 to EDIT MEMBER DETAILS";
        cout << "\n\tPress 5 to DELETE MEMBER";
        cout << "\n\tPress 6 to GO BACK TO MAIN MENU";
        cout << "\n\t**********************************************";
        cout << "\n\n\tOption: ";
        cin >> option;
        switch(option)
        {
            case 1: system("cls");
                    saveFitnessMember();
                    break;
                        
            case 2: showAllMembers();
                    break;
                        
            case 3:
                    int number;
                    system("cls");
                    cout << "\n\n\tPlease Enter The Member Number: ";
                    cin >> number;
                    displayFitnessRecord(number);
                    break;
                        
            case 4: editFitnessMember();
                    break;
                
            case 5: deleteFitnessMember();
                    break;
                    
            case 6: system("cls");
                    break;
                
            default: fitnessManagement();
        }
    }
}

void fitnessTips()
{
	cout << "Displaying fitness tips..." << endl;
	std::ifstream fitnessTipsFile("tips.txt");

	if (fitnessTipsFile.is_open())
	{
		cout << fitnessTipsFile.rdbuf();
		fitnessTipsFile.close();
	}
}

void userManagement()
{
	for(;;)
    {
        int choice;
        cout << "1. Join Fitness Club\n2. Quit Fitness Club\n3. Edit Your Profile\n";
        cout << endl << "Enter your choice: ";
        cin >> choice;
        switch(choice)
        {
            case 1: system("cls");
                    saveFitnessMember();
                    break;
            case 2: deleteFitnessMember();
                    break;
            case 3: editFitnessMember();
                    break;
        }
    }
}

int main()
{
	int mode, adminResult;
	cout << "Fitness Club Management System Project in C++" << endl;
	cout << endl << "SELECT MODE" << endl << "1. User" << endl << "2. Admin" << endl;
	cin >> mode;
	if(mode == 1)
	{
		cout << endl << "You're in User mode" << endl;
		userManagement();
	}
	else if(mode == 2)
	{
		cout << endl << "You're in Admin mode" << endl;
		AdminLogin admin;
		adminResult = admin.authenticateAdmin();
		if(adminResult == 1)
		{
			fitnessManagement();
		}
		else
		{
			cout << "You cannot access managerial details!";
		}
	}
	return 0;
}
