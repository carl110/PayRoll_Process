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




void CalculatePAYE();
void DisplayPaySlipSummary();
void MainMenu();
void EmployeeMaintenance();
void ShowAllEmployees();
void ShowIndividualEmployee(int employeeNo);
void AmendEmployee(int employeeNo);
void ShowAmendMenu(int employeeNo);
void AddNewEmployee();
bool CheckPPSExists(string ppsNo);
void RemoveEmployee();
bool CheckPPSNumber(string ppsNo);

vector<Employee> EmployeeVector;
void HardcodeEmployees();
vector<PaySlip> EmployeePaySlips;
void HardcodePayslips();

int main(int argc, const char * argv[]) {
    
    
    HardcodeEmployees();
    HardcodePayslips();
    
    MainMenu();
}

void HardcodeEmployees(){
    EmployeeVector.push_back({"Employer", "3569253TA", "Name", "Programmer", "IT", 52000});
    EmployeeVector.push_back({"Employer", "52314568PA", "Ian", "Cyber Security", "GIS", 104000});
}

void HardcodePayslips(){
    
    EmployeePaySlips.push_back({"3569253TA", 1000, 50, 250, 50, "1", 1000});
    EmployeePaySlips.push_back({"3569253TA", 1000, 50, 250, 50, "2", 2000});
    EmployeePaySlips.push_back({"3569253TA", 1000, 50, 250, 50, "3", 3000});
    EmployeePaySlips.push_back({"52314568PA", 2000, 100, 500, 100, "1", 2000});
    EmployeePaySlips.push_back({"52314568PA", 2000, 100, 500, 100, "2", 4000});
    EmployeePaySlips.push_back({"52314568PA", 2000, 100, 500, 100, "3", 6000});
}

void CalculatePAYE(){
    for(int i = 0; i < sizeof(EmployeeVector); i++){
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


void MainMenu(){
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
        MainMenu();
    }
    
    switch (selection) {
        case 1:
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            EmployeeMaintenance();
            break;
        case 2:
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            break;
        case 3:
            exit(0);
            break;
        default:
            break;
    }
};


void EmployeeMaintenance() {
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
        EmployeeMaintenance();
    }
    
    switch (menuChoice){
        case 1: //add
            AddNewEmployee();
            EmployeeMaintenance();
            break;
        case 2: //remove
            RemoveEmployee();
            EmployeeMaintenance();
            break;
        case 3: //view all
            ShowAllEmployees();
            EmployeeMaintenance();
            break;
        case 4: //amend
        {
            ShowAllEmployees();
            int employeeNo;
            cout << "Which record do you wish to amend? Enter Employee No...\n";
            cin >> employeeNo;
            ShowAmendMenu(employeeNo);
            EmployeeMaintenance();
        }
            break;
        case 5: //Return to Menu
            MainMenu();
            break;
        case 6:
            exit(0);
            break;
        default:
            EmployeeMaintenance();
            break;
    }
};

void RemoveEmployee(){
    
    string ppsNo;
    
    cout << "Enter Employees PPS Number\n";
    
    cin >> ppsNo;
    
    if (CheckPPSExists(ppsNo)){
        for (int i = 0; i < EmployeeVector.size(); i++ ){
            if (EmployeeVector[i].ppsNo == ppsNo){
                string name = EmployeeVector[i].name;
                EmployeeVector.erase(EmployeeVector.begin()+(i));
                i = sizeof(EmployeeVector);
                cout << "Employee" << name << " with PPS '" << ppsNo << "' has been removed from the system \n";
            }
        }
    } else {
        cout << "This PPS number does not exists, please check and try again \n";
    }
}

bool CheckPPSExists(string ppsNo){
    
    
    
    bool exists = false;
    
    for (int i = 0; i < EmployeeVector.size(); i++ ){
        if (EmployeeVector[i].ppsNo == ppsNo){
            exists = true;
            i = sizeof(EmployeeVector);
        }
    }
    return exists;
}

void AddNewEmployee(){
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
        
        if (CheckPPSExists(ppsNo)){
            cout << "This Employee already exists...\n\n";
            for (int i = 0; i < EmployeeVector.size(); i++){
                if (EmployeeVector[i].ppsNo == ppsNo){
                    ShowIndividualEmployee(i);
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
            EmployeeVector.push_back({employer, ppsNo, name, jobTitle, department, salary});
            cout << "Employee Added\n";
        }
    } else {
        cout << "This PPS Number is not valid, please try again...";
        EmployeeMaintenance();
    }
}

void ShowAllEmployees(){
    cout << "*************All Employees*************\n\n";
    for (int i = 0; i < EmployeeVector.size(); i++){
        cout << "Employer \t\t" << EmployeeVector[i].employer << "\n";
        cout << "Employee No \t" << i+1 << "\n";
        cout << "Name \t\t\t" << EmployeeVector[i].name << "\n";
        cout << "Department \t\t" << EmployeeVector[i].department << "\n";
        cout << "Job Title \t\t" << EmployeeVector[i].jobTitle << "\n";
        cout << "PPS Number \t\t" << EmployeeVector[i].ppsNo << "\n";
        cout << "******************************************************\n";
    }
    cout << "\n\n";
    
}

void ShowIndividualEmployee(int employeeNo){
    cout << "******************************************************\n";
    cout << "Employer \t\t" << EmployeeVector[employeeNo].employer << "\n";
    cout << "Employee No \t" << employeeNo + 1 << "\n";
    cout << "Name \t\t\t" << EmployeeVector[employeeNo].name << "\n";
    cout << "Department \t\t" << EmployeeVector[employeeNo].department << "\n";
    cout << "Job Title \t\t" << EmployeeVector[employeeNo].jobTitle << "\n";
    cout << "PPS Number \t\t" << EmployeeVector[employeeNo].ppsNo << "\n";
    cout << "******************************************************\n";
}

void ShowAmendMenu(int employeeNo){
    ShowIndividualEmployee(employeeNo - 1);
    
    
    cout << "Please select which detail you wish to change :\n";
    cout << "1  -  Employer Name \n";
    cout << "2  -  Employee Name \n";
    cout << "3  -  Employee PPS Number \n";
    cout << "4  -  Employees Job Title \n";
    cout << "5  -  Department Employee works in \n";
    cout << "6  -  Employees Salary \n";
    cout << "7  -  Exit \n";
    
    AmendEmployee(employeeNo);
}

void AmendEmployee(int employeeNo){
    
    string employeeData;
    int userSelection = 0;
    int salary = 0;
    
    
    cin >> userSelection;
    
    while (!cin >> userSelection) {
        cout << "INVALID INPUT.";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        AmendEmployee(employeeNo);
    }
    
    switch (userSelection) {
        case 1:
            cout << "Input the new Employer Name...\n";
            cin.ignore();
            getline(cin, employeeData);
            EmployeeVector[employeeNo - 1].employer = employeeData;
            break;
        case 2:
            cout << "Input the new Employee Name...\n";
            cin.ignore();
            getline(cin, employeeData);
            EmployeeVector[employeeNo - 1].name = employeeData;
            break;
        case 3:
            cout << "Input the new PPS Number...\n";
            cin >> employeeData;
            if (CheckPPSNumber(EmployeeVector[employeeNo - 1].ppsNo)){
                if (CheckPPSExists(employeeData)){
                    EmployeeVector[employeeNo - 1].ppsNo = employeeData;
                } else {
                    cout << "You cannot use a PPS number alread on the system";
                }} else {
                    cout << "The PPS Number you have entered is not valid, please try again...";
                    AmendEmployee(employeeNo);
                }
            break;
        case 4:
            cout << "Input the new Job Title...\n";
            cin.ignore();
            getline(cin, employeeData);
            EmployeeVector[employeeNo - 1].jobTitle = employeeData;
            break;
        case 5:
            cout << "Input the new Department Name...\n";
            cin.ignore();
            getline(cin, employeeData);
            EmployeeVector[employeeNo - 1].department = employeeData;
            break;
        case 6:
        {
            cout << "Input the new Salary...\n";
            cin >> salary;
            EmployeeVector[employeeNo - 1].salary = salary;
        }
            break;
        case 7:
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            EmployeeMaintenance();
            break;
        default:
            break;
    }
    cout << "\n\n\n\n\n\n\n\n\n\n\n";
    
    
    ShowAmendMenu(employeeNo);
    
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



void EmployeePayRoll(){
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
            MainMenu();
            break;
        case 5:
            exit(0);
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
