//
//  main.cpp
//  Payroll_Process
//
//  Created by Carl Wainwright on 06/10/2021.
//

#include <iostream>
#include <vector>

using namespace std;


struct Employee {
    string employer;
    string ppsNo;
    string name;
    string jobTitle;
    string department;
    double salary;
};

struct PaySlip {
    string ppsNo;
    double grossPay;
    double prsi; //5
    double paye; //25
    
    double usc; //5
    string payPeriod;
    double cumulatvePay;
};




void CalculatePAYE(vector<Employee>&ArrayOfEmployees);
void DisplayPaySlipSummary(vector<Employee>& ArrayOfEmployees, vector<PaySlip>& PaySlipVector);
void MainMenu(vector<Employee>& ArrayOfEmployees);
void EmployeeMaintenance(vector<Employee>& ArrayOfEmployees);
void ShowAllEmployees(vector<Employee>& ArrayOfEmployees);
void ShowIndividualEmployee(vector<Employee>& ArrayOfEmployees, int employeeNo);
void AmendEmployee(vector<Employee>& ArrayOfEmployees, int employeeNo);
void ShowAmendMenu(vector<Employee>& ArrayOfEmployees, int employeeNo);
void AddNewEmployee(vector<Employee>& ArrayOfEmployees);
bool CheckPPSExists(vector<Employee>& ArrayOfEmployees, string ppsNo);
void RemoveEmployee(vector<Employee>& ArrayOfEmployees);
bool CheckPPSNumber(string ppsNo);



int main(int argc, const char * argv[]) {
    
    
    vector<Employee> EmployeeVec = {{"Employer" , "3569253TA", "Name", "Programmer", "IT", 52000},
        {"Employer", "52314568PA", "Ian", "Cyber Security", "GIS", 104000}};
    
    vector<PaySlip> EmployeePaySlips{{"3569253TA", 1000, 50, 250, 50, "1", 1000},
        {"3569253TA", 1000, 50, 250, 50, "2", 2000},
        {"3569253TA", 1000, 50, 250, 50, "3", 3000},
        {"52314568PA", 2000, 100, 500, 100, "1", 2000},
        {"52314568PA", 2000, 100, 500, 100, "2", 4000},
        {"52314568PA", 2000, 100, 500, 100, "3", 6000}
    };
    
    MainMenu(EmployeeVec);
}

void CalculatePAYE(vector<Employee>&ArrayOfEmployees){
    for(int i = 0; i < sizeof(ArrayOfEmployees); i++){
        //        ArrayOfEmployees[i].paye = ArrayOfEmployees[i].weeklyPay * 0.27;
    }
}

void DisplayPaySlipSummary(vector<Employee>& ArrayOfEmployees, vector<PaySlip>& PaySlipVector){
    
    for (int i = 0; i < ArrayOfEmployees.size(); i++)
    {
        cout << "Employer " << ArrayOfEmployees[i].employer << "\t";
        cout << "Name " << ArrayOfEmployees[i].name << "\t";
        cout << "Department " << ArrayOfEmployees[i].department << "\t";
        cout << "Job Title " << ArrayOfEmployees[i].jobTitle << "\t";
        cout << "PPS Number " << ArrayOfEmployees[i].ppsNo << "\t";
        
        for (int n = 0; n < PaySlipVector.size(); n++)
        {
            if (PaySlipVector[n].ppsNo == ArrayOfEmployees[i].ppsNo)
            {
                
                cout << "GrossPay = " << PaySlipVector[n].grossPay << "\n";
                cout << "PRSI = " << PaySlipVector[n].prsi << "\n"; //5
                cout << "PAYE = " << PaySlipVector[n].paye << "\n"; //25
                cout << "USC = " << PaySlipVector[n].usc << "\n"; //5
                cout << "Pay Period = " << PaySlipVector[n].payPeriod << "\n";
                cout << "Cumulative Pay = " << PaySlipVector[n].cumulatvePay << "\n";
            }
        }
        
    }
}


void MainMenu(vector<Employee>& ArrayOfEmployees){
    int selection;
    cout << "*************PAYROLL SYSTEM*************" << "\n\n";
    cout << "1  -  Employee Maintenance \n";
    cout << "2  -  Pay Roll Summary \n";
    cout << "3  -  Exit Program \n";
    
    cin >> selection;
    
    while (!cin >> selection) {
        cout << "INVALID INPUT.";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        MainMenu(ArrayOfEmployees);
    }
    
    switch (selection) {
        case 1:
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            EmployeeMaintenance(ArrayOfEmployees);
            break;
        case 2:
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            break;
        default:
            break;
    }
};


void EmployeeMaintenance(vector<Employee>& ArrayOfEmployees) {
    int menuChoice = 0;
    cout << "*************Employee Maintenance*************" << "\n\n";
    cout << "1  -  Add Employee \n";
    cout << "2  -  Remove Employee \n";
    cout << "3  -  View All Employees \n";
    cout << "4  -  Amend Employee Data \n";
    cout << "5  -  Return to Main Menu \n";
    cout << "6  -  Exit Program \n";
    cin >> menuChoice;
    
    while (!cin >> menuChoice) {
        cout << "INVALID INPUT.";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        EmployeeMaintenance(ArrayOfEmployees);
    }
    
    switch (menuChoice){
        case 1: //add
            AddNewEmployee(ArrayOfEmployees);
            EmployeeMaintenance(ArrayOfEmployees);
            break;
        case 2: //remove
            RemoveEmployee(ArrayOfEmployees);
            EmployeeMaintenance(ArrayOfEmployees);
            break;
        case 3: //view all
            ShowAllEmployees(ArrayOfEmployees);
            EmployeeMaintenance(ArrayOfEmployees);
            break;
        case 4: //amend
        {
            ShowAllEmployees(ArrayOfEmployees);
            int employeeNo;
            cout << "Which record do you wish to amend? Enter Employee No...\n";
            cin >> employeeNo;
            ShowAmendMenu(ArrayOfEmployees, employeeNo);
            EmployeeMaintenance(ArrayOfEmployees);
        }
            break;
        case 5: //Return to Menu
            MainMenu(ArrayOfEmployees);
            break;
        case 6:
            break;
        default:
            EmployeeMaintenance(ArrayOfEmployees);
            break;
    }
};

void RemoveEmployee(vector<Employee>& ArrayOfEmployees){
    
    string ppsNo;
    
    cout << "Enter Employees PPS Number\n";
    
    cin >> ppsNo;
    
    if (CheckPPSExists(ArrayOfEmployees, ppsNo)){
        for (int i = 0; i < ArrayOfEmployees.size(); i++ ){
            if (ArrayOfEmployees[i].ppsNo == ppsNo){
                string name = ArrayOfEmployees[i].name;
                ArrayOfEmployees.erase(ArrayOfEmployees.begin()+(i));
                i = sizeof(ArrayOfEmployees);
                cout << "Employee" << name << " with PPS '" << ppsNo << "' has been removed from the system \n";
            }
        }
    } else {
        cout << "This PPS number does not exists, please check and try again \n";
    }
}

bool CheckPPSExists(vector<Employee>& ArrayOfEmployees, string ppsNo){
    
    
    
    bool exists = false;
    
    for (int i = 0; i < ArrayOfEmployees.size(); i++ ){
        if (ArrayOfEmployees[i].ppsNo == ppsNo){
            exists = true;
            i = sizeof(ArrayOfEmployees);
        }
    }
    return exists;
}

void AddNewEmployee(vector<Employee>& ArrayOfEmployees){
    string employer;
    string ppsNo;
    string name;
    string jobTitle;
    string department;
    double salary;
    
    //check if employee already exists
    cout << "\n\n\n\n\n\n";
    cout << "Enter PPS Number...";
    cin >> ppsNo;
    
    if (CheckPPSNumber(ppsNo)){
        
        if (CheckPPSExists(ArrayOfEmployees, ppsNo)){
            cout << "This Employee already exists...\n\n";
            for (int i = 0; i < ArrayOfEmployees.size(); i++){
                if (ArrayOfEmployees[i].ppsNo == ppsNo){
                    ShowIndividualEmployee(ArrayOfEmployees, i);
                }
            }
            
        } else {
            cin.ignore();
            cout << "Enter Employer Name...";
            getline(cin, employer);
            cout << "Enter Employee Name...";
            getline(cin, name);
            cout << "Enter Job Title...";
            getline(cin, jobTitle);
            cout << "Enter Department Name...";
            getline(cin, department);
            cout << "Enter Salary (Numbers only)...";
            cin >> salary;
            ArrayOfEmployees.push_back({employer, ppsNo, name, jobTitle, department, salary});
            cout << "Employee Added\n";
        }
    } else {
        cout << "This PPS Number is not valid, please try again...";
        EmployeeMaintenance(ArrayOfEmployees);
    }
}

void ShowAllEmployees(vector<Employee>& ArrayOfEmployees){
    cout << "*************All Employees*************\n\n";
    for (int i = 0; i < ArrayOfEmployees.size(); i++){
        cout << "Employer \t\t" << ArrayOfEmployees[i].employer << "\n";
        cout << "Employee No \t" << i+1 << "\n";
        cout << "Name \t\t\t" << ArrayOfEmployees[i].name << "\n";
        cout << "Department \t\t" << ArrayOfEmployees[i].department << "\n";
        cout << "Job Title \t\t" << ArrayOfEmployees[i].jobTitle << "\n";
        cout << "PPS Number \t\t" << ArrayOfEmployees[i].ppsNo << "\n";
        cout << "******************************************************\n";
    }
    cout << "\n\n";
    
}

void ShowIndividualEmployee(vector<Employee>& ArrayOfEmployees, int employeeNo){
    cout << "******************************************************\n";
    cout << "Employer \t\t" << ArrayOfEmployees[employeeNo].employer << "\n";
    cout << "Employee No \t" << employeeNo + 1 << "\n";
    cout << "Name \t\t\t" << ArrayOfEmployees[employeeNo].name << "\n";
    cout << "Department \t\t" << ArrayOfEmployees[employeeNo].department << "\n";
    cout << "Job Title \t\t" << ArrayOfEmployees[employeeNo].jobTitle << "\n";
    cout << "PPS Number \t\t" << ArrayOfEmployees[employeeNo].ppsNo << "\n";
    cout << "******************************************************\n";
}

void ShowAmendMenu(vector<Employee>& ArrayOfEmployees, int employeeNo){
    ShowIndividualEmployee(ArrayOfEmployees, employeeNo - 1);
    
    
    cout << "Please select which detail you wish to change :\n";
    cout << "1  -  Employer Name \n";
    cout << "2  -  Employee Name \n";
    cout << "3  -  Employee PPS Number \n";
    cout << "4  -  Employees Job Title \n";
    cout << "5  -  Department Employee works in \n";
    cout << "6  -  Employees Salary \n";
    cout << "7  -  Exit \n";
    
    AmendEmployee(ArrayOfEmployees, employeeNo);
}

void AmendEmployee(vector<Employee>& ArrayOfEmployees, int employeeNo){
    
    string employeeData;
    int userSelection;
    int salary = 0;
    
    
    cin >> userSelection;
    
    while (!cin >> userSelection) {
        cout << "INVALID INPUT.";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        AmendEmployee(ArrayOfEmployees, employeeNo);
    }
    
    switch (userSelection) {
        case 1:
            cout << "Input the new Employer Name...\n";
            cin.ignore();
            getline(cin, employeeData);
            ArrayOfEmployees[employeeNo - 1].employer = employeeData;
            break;
        case 2:
            cout << "Input the new Employee Name...\n";
            cin.ignore();
            getline(cin, employeeData);
            ArrayOfEmployees[employeeNo - 1].name = employeeData;
            break;
        case 3:
            cout << "Input the new PPS Number...\n";
            cin >> employeeData;
            if (CheckPPSNumber(ArrayOfEmployees[employeeNo - 1].ppsNo)){
                if (CheckPPSExists(ArrayOfEmployees, employeeData)){
                    ArrayOfEmployees[employeeNo - 1].ppsNo = employeeData;
                } else {
                    cout << "You cannot use a PPS number alread on the system";
                }} else {
                    cout << "The PPS Number you have entered is not valid, please try again...";
                    AmendEmployee(ArrayOfEmployees, employeeNo);
                }
            break;
        case 4:
            cout << "Input the new Job Title...\n";
            cin.ignore();
            getline(cin, employeeData);
            ArrayOfEmployees[employeeNo - 1].jobTitle = employeeData;
            break;
        case 5:
            cout << "Input the new Department Name...\n";
            cin.ignore();
            getline(cin, employeeData);
            ArrayOfEmployees[employeeNo - 1].department = employeeData;
            break;
        case 6:
        {
            cout << "Input the new Salary...\n";
            cin >> salary;
            ArrayOfEmployees[employeeNo - 1].salary = salary;
        }
            break;
        case 7:
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            EmployeeMaintenance(ArrayOfEmployees);
            break;
        default:
            break;
    }
    cout << "\n\n\n\n\n\n\n\n\n\n\n";
    
    
    ShowAmendMenu(ArrayOfEmployees, employeeNo);
    
}

bool CheckPPSNumber(string ppsNo){
    
    if (ppsNo.length() == 9 || ppsNo.length() == 10){
        for (int i = 0; i < 7; i++){
            if (isdigit(ppsNo[i]) == false){
                return false;
            }
        } return true;
    } else {
        return false;
    }
}



void EmployeePayRoll(vector<Employee>& ArrayOfEmployees, vector<PaySlip>& PaySlipVector){
    int menuChoice = 0;
    cout << "*************Pay Roll Summary*************" << "\n\n";
    cout << "1  -  Compute Payroll for Employee \n";
    cout << "2  -  Display Payroll History for Employee \n";
    cout << "3  -  Display All Employees Payslip History \n";
    cout << "4  -  Return to Main Menu \n";
    cout << "5  -  Exit Program \n";
    cin >> menuChoice;
    
    while (!cin >> menuChoice) {
        cout << "INVALID INPUT.";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
//        EmployeePayRoll(ArrayOfEmployees);
    }
    
    switch (menuChoice){
        case 1: //Compute Payroll for Employee
            
            break;
        case 2: //Display Payroll History for Employee
            
            break;
        case 3: //Display All Employees Payslip History
//            DisplayPaySlipSummary(ArrayOfEmployees, PaySlipVector)
            break;
        case 4: //Return to Menu
            MainMenu(ArrayOfEmployees);
            break;
        case 5:
            break;
        default:
            break;
    }
}

void ComputePayRoll(){
    
}

void DisplayPayrollHistoryForIndividual(){
    
}

void DisplayPayrollHistoryForAll(vector<Employee>& ArrayOfEmployees, vector<PaySlip>& PaySlipVector){
    
}

//
//
//void DisplayPaySlipSummary(vector<Employee>& ArrayOfEmployees, vector<PaySlip>& PaySlipVector){
//
//
//}
