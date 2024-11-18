#include <iostream>
#include <string>  
#include <cmath>
#include <fstream>


using namespace std;

int main() {
    double speedofLight = 300000000;
    double PI = 3.1415926535897932384626433832795028841971693993751058209;

    //input variables for signal 1
    double amp1, fre1, iniphase1, t1 = 0, x1 = 0;  
    string test;  
    
    cout << "For signal 1 enter the following values: " << endl;

    do{
        cout << "Amplitude in volts: " << endl;
        cin >> amp1;
        if (amp1 <= 0) {
            cout << "Error: Amplitude must be greater than zero.\n";
        }
    }while(amp1<=0);


    do{
        cout << "Frequency in radians: " << endl;
        cin >> fre1;
        if (fre1 <= 0) {
            cout << "Error: Frequency must be a positive value.\n";
        }
    }while(fre1<=0);

    cout << "Initial phase in radians: " << endl;
    cin >> iniphase1;  

    //input handling for t1 and x1
    do {
        cout << "Do you want to input t1 or x1? (Enter 't1' or 'x1'): " << endl;
        cin >> test;
        if (test != "t1" && test != "x1") {
            cerr << "Error: Invalid choice. Please enter 't1' or 'x1'.\n";
        }
    } while (test != "t1" && test != "x1");

    // Time (t1) or Distance (x1)
    if (test == "t1") {
        do {
            cout << "Enter t1 (must be non-negative): " << endl;
            cin >> t1;
            if (t1 < 0) {
                cerr << "Error: t1 cannot be negative. Please try again.\n";
            }
        } while (t1 < 0);
    } else if (test == "x1") {
        do {
            cout << "Enter x1 (must be non-negative): " << endl;
            cin >> x1;
            if (x1 < 0) {
                cerr << "Error: x1 cannot be negative. Please try again.\n";
            }
        } while (x1 < 0);
    }


    //initialize other variables for signal 1

    double wavelength1=speedofLight/fre1;
    double angfre1=2*PI*fre1;
    double wavenum1=(2*PI)/wavelength1;


    //input variables for signal 2 
    double amp2, fre2, iniphase2, t2 = 0, x2 = 0;  
    string test2;  

    cout << "For signal 2 enter the following values: " << endl;
    do{
        cout << "Amplitude in volts: " << endl;
        cin >> amp2;
        if (amp2 <= 0) {
            cout << "Error: Amplitude must be greater than zero.\n";
        }
    }while(amp2<=0);

    do{
        cout << "Frequency in radians: " << endl;
        cin >> fre2;
        if (fre2 <= 0) {
            cout << "Error: Frequency must be a positive value.\n";
        }
    }while(fre2<=0);

    cout << "Initial phase in radians: " << endl;
    cin >> iniphase2;
    
    //input handling for t2 and x2
    do {
        cout << "Do you want to input t2 or x2? (Enter 't2' or 'x2'): " << endl;
        cin >> test2;
        if (test2 != "t2" && test2 != "x2") {
            cerr << "Error: Invalid choice. Please enter 't2' or 'x2'.\n";
        }
    } while (test2 != "t2" && test2 != "x2");

    // Time (t2) or Distance (x2)
    if (test2 == "t2") {
        do {
            cout << "Enter t2 (must be non-negative): " << endl;
            cin >> t2;
            if (t2 < 0) {
                cerr << "Error: t2 cannot be negative. Please try again.\n";
            }
        } while (t2 < 0);
    } else if (test2 == "x2") {
        do {
            cout << "Enter x2 (must be non-negative): " << endl;
            cin >> x2;
            if (x2 < 0) {
                cerr << "Error: x2 cannot be negative. Please try again.\n";
            }
        } while (x2 < 0);
    }

    //initialize other variables for signal 2

    double wavelength2=speedofLight/fre2;
    double angfre2=2*PI*fre2;
    double wavenum2=(2*PI)/wavelength2;


    //calculate signals 1 and 2 with the equation 

    double D1= amp1 * sin ( (wavenum1 * x1) + (angfre1 * t1) +iniphase1 );
    double D2= amp2 * sin ( (wavenum2 * x2) + (angfre2 * t2) +iniphase2 );

    // Prepare data for plotting
    ofstream data("signals.dat"); // File to store the data

    double x_max = 10; // Maximum distance or time for plotting
    double x_step = 0.005; // Step size

    // Generate signal values over a range and write to file
    for (double x = 0; x <= x_max; x += x_step) {
        // Calculate signal values based on time or distance input
        double D1 = (test == "t1") ? amp1 * sin(wavenum1 * x1 + angfre1 * x + iniphase1)
                                   : amp1 * sin(wavenum1 * x + angfre1 * t1 + iniphase1);
        
        double D2 = (test2 == "t2") ? amp2 * sin(wavenum2 * x2 + angfre2 * x + iniphase2)
                                    : amp2 * sin(wavenum2 * x + angfre2 * t2 + iniphase2);

        double D_sum = D1 + D2;
        
        // Write the values of x, D1, D2, and the sum to the file
        data << x << " " << D1 << " " << D2 << " " << D_sum << endl;
    }
    data.close();

    // Plotting using gnuplot
    FILE *gnuplotPipe = _popen("C:\\\"Program Files\"\\gnuplot\\bin\\gnuplot.exe", "w");;
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "set title 'Signal Interference'\n");
        fprintf(gnuplotPipe, "set xlabel 'Distance or Time'\n");
        fprintf(gnuplotPipe, "set ylabel 'Amplitude'\n");
        fprintf(gnuplotPipe, "plot 'signals.dat' using 1:2 title 'Signal 1' with lines, ");
        fprintf(gnuplotPipe, "'signals.dat' using 1:3 title 'Signal 2' with lines, ");
        fprintf(gnuplotPipe, "'signals.dat' using 1:4 title 'Sum of Signals' with lines\n");
        fflush(gnuplotPipe);
        system("pause");
        _pclose(gnuplotPipe);
    } else {
        cerr << "Error: Could not open gnuplot for plotting.\n";
    }

    return 0;
}
