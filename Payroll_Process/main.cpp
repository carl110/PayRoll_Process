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
    double prsi; //5%
    double paye; //25%
    double usc; //5%
    int payPeriod;
    double cumulatvePay;
};

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
void EmployeePayRoll();
void ComputePayRoll();
void DisplayPayrollHistoryForIndividual();
void DisplayPayrollHistoryForAll();
string ChangeToUpperCase(string userInput);

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
    EmployeeVector.push_back({"TEC INC", "3214567TA", "John Murphey", "Programmer", "IT", 56000});
    EmployeeVector.push_back({"TEC INC", "5413726W", "Jaime King", "Cyber Security", "GIS", 72000});
}

void HardcodePayslips(){
    EmployeePaySlips.push_back({"3214567TA", 1076.92, 53.85, 269.23, 53.85, 1, 1076.92});
    EmployeePaySlips.push_back({"3214567TA", 1076.92, 53.85, 269.23, 53.85, 2, 2153.84});
    EmployeePaySlips.push_back({"3214567TA", 1076.92, 53.85, 269.23, 53.85, 3, 3230.76});
    EmployeePaySlips.push_back({"5413726W", 1384.62, 69.23, 346.15, 69.23, 1, 1384.62});
    EmployeePaySlips.push_back({"5413726W", 1384.62, 69.23, 346.15, 69.23, 2, 2769.24});
    EmployeePaySlips.push_back({"5413726W", 1384.62, 69.23, 346.15, 69.23, 3, 4153.86});
}

string ChangeToUpperCase(string userInput){ //Change the input string to all uppercase
    std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
    return userInput;
}

bool IsInputEmpty(string userInput){//Check if user input is empty
    //Remove all whitespaces first
    userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end());
    if (userInput.length() == 0){
        return true;
    } else {
        return false;
    }
}

bool isNumber( const string& s ){
  bool hitDecimal=0;
  for( char c : s )
  {
    if( c=='.' && !hitDecimal )
      hitDecimal=1; // 1 decimal place is fine
    else if( !isdigit( c ) )
      return 0 ; // not a string
  }
  return 1 ;
}

void MainMenu(){
    int selection;
    cout << "*************PAYROLL SYSTEM*************" << "\n\n";
    cout << "1  -  Employee Maintenance \n";
    cout << "2  -  Pay Roll Summary \n";
    cout << "3  -  Exit Program \n";
    
    cin >> selection;
    
    switch (selection) {
        case 1://Employee Maintenance
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            EmployeeMaintenance();
            break;
        case 2: // Pay Roll Summary
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            EmployeePayRoll();
            break;
        case 3: //Exit Application
            exit(0);
            break;
        default: //If input is not recognised on switch then throw error and redisplay options
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            cout << "*************INVALID INPUT.*************\n" << "\tPlease enter a valid selection\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            MainMenu();
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
            string employeeNo;
            cout << "Which record do you wish to amend? Enter Employee No...\n";
            cin.ignore();
            getline(cin, employeeNo);
            //Check input is a valid selection
            while (!isNumber(employeeNo) || IsInputEmpty(employeeNo) || stoi(employeeNo) > EmployeeVector.size()){
                cout << "You must input a valid Employee number from above...\n";
                getline(cin, employeeNo);
            }
            
            ShowAmendMenu(stoi(employeeNo));
            EmployeeMaintenance();
        }
            break;
        case 5: //Return to Menu
            MainMenu();
            break;
        case 6: //Exit application
            exit(0);
            break;
        default: //If input is not recognised on switch then throw error and redisplay options
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            cout << "*************INVALID INPUT.*************\n" << "\tPlease enter a valid selection\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            EmployeeMaintenance();
            break;
    }
};

void RemoveEmployee(){
    string ppsNo;
    cout << "Enter Employees PPS Number\n";
    cin >> ppsNo;
    ppsNo = ChangeToUpperCase(ppsNo);
    //First check if PPS is exists
    if (CheckPPSExists(ppsNo)){
        for (int i = 0; i < EmployeeVector.size(); i++ ){
            if (EmployeeVector[i].ppsNo == ppsNo){ //Remove vector item based on PPS number
                string name = EmployeeVector[i].name;
                EmployeeVector.erase(EmployeeVector.begin()+(i));
                i = sizeof(EmployeeVector);
                cout << "\n\n*******************************************************************************************************\n";
                cout << "Employee " << name << ", with PPS '" << ppsNo << "', has been removed from the system \n";
                cout << "*******************************************************************************************************\n\n";
            }
        }
    } else {
        cout << "This PPS number does not exists, please check and try again \n\n";
    }
}

bool CheckPPSExists(string ppsNo){
    bool exists = false;
    //Loop through vector to see if PPS exists
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
    string salaryString;
    double salary;
    
    //check if employee already exists
    cout << "\n\n\n\n\n\n";
    cout << "Enter PPS Number...\n";
    cin >> ppsNo;
    ppsNo =  ChangeToUpperCase(ppsNo);
    //Check if PPS number is a valid PPS
    if (CheckPPSNumber(ppsNo)){
        if (CheckPPSExists(ppsNo)){
            cout << "This Employee already exists...\n\n";
            for (int i = 0; i < EmployeeVector.size(); i++){
                if (EmployeeVector[i].ppsNo == ppsNo){
                    ShowIndividualEmployee(i);
                }
            }
        } else {
            cin.ignore(); //Allow input with whitespace using getline
            cout << "Enter Employer Name...\n";
            getline(cin, employer);
            while (IsInputEmpty(employer)){
                cout << "You cannot leave the Employer Name empty. Please enter Employer Name...\n";
                getline(cin, employer);
            }
            cout << "Enter Employee Name...\n";
            getline(cin, name);
            while (IsInputEmpty(name)){
                cout << "You cannot leave the Employees Name empty. Please enter Employees Name...\n";
                getline(cin, name);
            }
            cout << "Enter Job Title...\n";
            getline(cin, jobTitle);
            while (IsInputEmpty(jobTitle)){
                cout << "You cannot leave the Job Title empty. Please enter Job Title...\n";
                getline(cin, jobTitle);
            }
            cout << "Enter Department Name...\n";
            getline(cin, department);
            while (IsInputEmpty(department)){
                cout << "You cannot leave the Department Name empty. Please enter Department Name...\n";
                getline(cin, department);
            }
            cout << "Enter Salary (Numbers only)...\n";
            getline(cin, salaryString);
            
            //Check input is a value and also not empty
            while (!isNumber(salaryString) || IsInputEmpty(salaryString)) {
                cout << "You must enter a value for salary in numbers only...\n";
                getline(cin, salaryString);
            }
            
            salary = stod(salaryString);

            //Add employee to vector
            EmployeeVector.push_back({employer, ppsNo, name, jobTitle, department, salary});
            cout << "\n\n*******************************************************************************************************\n";
            cout << "Employee " << name << ", with PPS '" << ppsNo << "', has been added to the system \n";
            cout << "*******************************************************************************************************\n\n";
        }
    } else {
        cout << "This PPS Number is not valid, please try again...\n\n";
        EmployeeMaintenance();
    }
}

void ShowAllEmployees(){
    cout << "\n*************All Employees*************\n\n";
    for (int i = 0; i < EmployeeVector.size(); i++){
        cout << "Employer \t\t\t" << EmployeeVector[i].employer << "\n";
        cout << "Employee No \t\t" << i+1 << "\n";
        cout << "Name \t\t\t\t" << EmployeeVector[i].name << "\n";
        cout << "Department \t\t\t" << EmployeeVector[i].department << "\n";
        cout << "Job Title \t\t\t" << EmployeeVector[i].jobTitle << "\n";
        cout << "PPS Number \t\t\t" << EmployeeVector[i].ppsNo << "\n";
        cout << "Employee Salary \t\t" <<EmployeeVector[i].salary << "\n";
        cout << "******************************************************\n";
    }
    cout << "\n\n";
}

void ShowIndividualEmployee(int employeeNo){
    cout << "\n******************************************************\n";
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
    string salaryString;
    double salary = 0;
    cin >> userSelection;
    
    switch (userSelection) {
        case 1:
            cout << "Input the new Employer Name...\n";
            cin.ignore();
            getline(cin, employeeData);
            while (IsInputEmpty(employeeData)){
                cout << "You cannot leave the Employer Name empty. Please enter Employer Name...\n";
                getline(cin, employeeData);
            }
            EmployeeVector[employeeNo - 1].employer = employeeData;
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            break;
        case 2:
            cout << "Input the new Employee Name...\n";
            cin.ignore();
            getline(cin, employeeData);
            while (IsInputEmpty(employeeData)){
                cout << "You cannot leave the Employee Name empty. Please enter Employee Name...\n";
                getline(cin, employeeData);
            }
            EmployeeVector[employeeNo - 1].name = employeeData;
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            break;
        case 3:
            cout << "Input the new PPS Number...\n";
            cin.ignore();
            getline(cin, employeeData);
            employeeData = ChangeToUpperCase(employeeData);
            //Check PPS does not Exist in current vector and it is a valid PPS number format
            if (CheckPPSNumber(employeeData)){
                if (!CheckPPSExists(employeeData)){
                    EmployeeVector[employeeNo - 1].ppsNo = employeeData;
                } else {
                    cout << "\n\n\n\nThis PPS number is currently used by another employee on the system\n";
                }} else {
                    cout << "\n\n\n\nThe PPS Number you have entered is not valid, please try again...\n";
                    ShowAmendMenu(employeeNo);
                    cout << "\n\n\n\n\n\n\n\n\n\n\n";
                }
            break;
        case 4:
            cout << "Input the new Job Title...\n";
            cin.ignore();
            getline(cin, employeeData);
            while (IsInputEmpty(employeeData)){
                cout << "You cannot leave the Job Title empty. Please enter Job Title...\n";
                getline(cin, employeeData);
            }
            EmployeeVector[employeeNo - 1].jobTitle = employeeData;
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            break;
        case 5:
            cout << "Input the new Department Name...\n";
            cin.ignore();
            getline(cin, employeeData);
            while (IsInputEmpty(employeeData)){
                cout << "You cannot leave the Department Name empty. Please enter Department Name...\n";
                getline(cin, employeeData);
            }
            EmployeeVector[employeeNo - 1].department = employeeData;
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            break;
        case 6:
            cout << "Input the new Salary...\n";
            cin >> salaryString;
            //Check input is a value and also not empty
            while (!isNumber(salaryString) || IsInputEmpty(salaryString)) {
                cout << "You must enter a value for salary in numbers only...\n";
                getline(cin, salaryString);
            }
            salary = stod(salaryString);
            EmployeeVector[employeeNo - 1].salary = salary;
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            break;
        case 7: //Go back to emploee Maintenance
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            EmployeeMaintenance();
            break;
        default: //If input is not recognised on switch then throw error and redisplay options
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            cout << "*************INVALID INPUT.*************\n" << "\tPlease enter a valid selection\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            ShowAmendMenu(employeeNo);
            break;
    }
    ShowAmendMenu(employeeNo);
}

bool CheckPPSNumber(string ppsNo){
    //PPS is 7 digits with 1 or 2 letters after
    if (ppsNo.length() == 8 || ppsNo.length() == 9){
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
    cout << "\n*************Pay Roll Summary*************" << "\n\n";
    cout << "1  -  Compute Payroll for Employee \n";
    cout << "2  -  Display Payroll History for Individual Employee \n";
    cout << "3  -  Display All Employees Payslip History \n";
    cout << "4  -  Return to Main Menu \n";
    cout << "5  -  Exit Program \n";
    cin >> menuChoice;
    
    switch (menuChoice){
        case 1: //Compute Payroll for Employee
            ComputePayRoll();
            EmployeePayRoll();
            break;
        case 2: //Display Payroll History for Employee
            DisplayPayrollHistoryForIndividual();
            EmployeePayRoll();
            break;
        case 3: //Display All Employees Payslip History
            DisplayPayrollHistoryForAll();
            EmployeePayRoll();
            break;
        case 4: //Return to Menu
            MainMenu();
            break;
        case 5: //Exit Application
            exit(0);
            break;
        default: //If input is not recognised on switch then throw error and redisplay options
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            cout << "*************INVALID INPUT.*************\n" << "\tPlease enter a valid selection\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            EmployeePayRoll();
            break;
    }
}

void ComputePayRoll(){
    string ppsNo;
    double weeklyRate = 0;
    int payPeriod = 1;
    double prsi = 0;
    double paye = 0;
    double usc = 0;
    
    cout << "Enter Employees PPS Number...\n";
    cin >> ppsNo;
    ppsNo = ChangeToUpperCase(ppsNo);
    //Check if PPS Exists
    if (CheckPPSExists(ppsNo)){
        for (int i = 0; i < EmployeeVector.size(); i++ ){
            if (EmployeeVector[i].ppsNo == ppsNo){
                //Show name and PPS of individual

                    if (EmployeeVector[i].ppsNo == ppsNo){
                        cout << "\n\n******************************************************\n";
                        cout << EmployeeVector[i].name << "\t";
                        cout << "PPS Number " << EmployeeVector[i].ppsNo << "\t\n\n";
                        weeklyRate = static_cast<int>((EmployeeVector[i].salary / 52) * 10 + 0.5) / 10.0;
                    }
                    
                    for (int n = 0; n < EmployeePaySlips.size(); n++)
                    {
                        if (EmployeePaySlips[n].ppsNo == ppsNo)
                        {
                            payPeriod++;
                        }
                    }
                    //Loop through and show all payslips associated
                
                prsi = static_cast<int>((weeklyRate * 0.05) * 10 + 0.5) / 10.0;
                paye = static_cast<int>((weeklyRate * 0.25) * 10 + 0.5) / 10.0;
                usc = static_cast<int>((weeklyRate * 0.05) * 10 + 0.5) / 10.0;
                
                EmployeePaySlips.push_back({ppsNo, weeklyRate, prsi, paye, usc, payPeriod, weeklyRate * payPeriod});

                            cout << "Pay Period = " << payPeriod << "\n";
                            cout << "GrossPay = " << weeklyRate << "\n";
                            cout << "PRSI = " << prsi << "\n"; //5
                            cout << "PAYE = " << paye << "\n"; //25
                            cout << "USC = " << usc << "\n"; //5
                            cout << "Cumulative Pay = " << weeklyRate * payPeriod << "\n";
                            cout << "******************************************************\n";
                i = sizeof(EmployeeVector);
            }
            
        }
    } else {
        cout << "This PPS number does not exists, please check and try again \n";
    }
}

void DisplayPayrollHistoryForIndividual(){
    string ppsNo;
    cout << "Enter Employees PPS Number...\n";
    cin >> ppsNo;
    ppsNo = ChangeToUpperCase(ppsNo);
    //Check if PPS Exists
    if (CheckPPSExists(ppsNo)){
        for (int i = 0; i < EmployeeVector.size(); i++ ){
            if (EmployeeVector[i].ppsNo == ppsNo){
                //Show name and PPS of individual
                for (int i = 0; i < EmployeeVector.size(); i++)
                {
                    if (EmployeeVector[i].ppsNo == ppsNo){
                        cout << "\n\n******************************************************\n";
                        cout << EmployeeVector[i].name << "\t";
                        cout << "PPS Number " << EmployeeVector[i].ppsNo << "\t\n\n";
                    //Loop through and show all payslips associated
                    for (int n = 0; n < EmployeePaySlips.size(); n++)
                    {
                        if (EmployeePaySlips[n].ppsNo == ppsNo)
                        {
                            cout << "Pay Period = " << EmployeePaySlips[n].payPeriod << "\n";
                            cout << "GrossPay = " << EmployeePaySlips[n].grossPay << "\n";
                            cout << "PRSI = " << EmployeePaySlips[n].prsi << "\n"; //5
                            cout << "PAYE = " << EmployeePaySlips[n].paye << "\n"; //25
                            cout << "USC = " << EmployeePaySlips[n].usc << "\n"; //5
                            cout << "Cumulative Pay = " << EmployeePaySlips[n].cumulatvePay << "\n";
                            cout << "******************************************************\n";
                        }
                    }
                    }
                }
            }
        }
    } else {
        cout << "This PPS number does not exists, please check and try again \n";
    }
}

void DisplayPayrollHistoryForAll(){
    //Loop through all employees and display
    for (int i = 0; i < EmployeeVector.size(); i++)
    {
        cout << "\n\n******************************************************\n";
        cout << EmployeeVector[i].name << "\t";
        cout << "PPS Number " << EmployeeVector[i].ppsNo << "\t\n\n";
        //Loop through payslips and show associated with each employee
        for (int n = 0; n < EmployeePaySlips.size(); n++)
        {
            if (EmployeePaySlips[n].ppsNo == EmployeeVector[i].ppsNo)
            {
                cout << "Pay Period = " << EmployeePaySlips[n].payPeriod << "\n";
                cout << "GrossPay = " << EmployeePaySlips[n].grossPay << "\n";
                cout << "PRSI = " << EmployeePaySlips[n].prsi << "\n"; //5
                cout << "PAYE = " << EmployeePaySlips[n].paye << "\n"; //25
                cout << "USC = " << EmployeePaySlips[n].usc << "\n"; //5
                cout << "Cumulative Pay = " << EmployeePaySlips[n].cumulatvePay << "\n";
                cout << "******************************************************\n";
            }
        }
    }

}
