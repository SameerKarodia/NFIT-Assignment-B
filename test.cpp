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

    cout << "Amplitude in volts: " << endl;
    cin >> amp1;
    cout << "Frequency in radians: " << endl;
    cin >> fre1;
    cout << "Initial phase in radians: " << endl;
    cin >> iniphase1;
    
    cout << "Do you want to input t1 or x1? " << endl;
    cin >> test;  

    if (test == "t1") {
        cout << "Enter t1: " << endl;
        cin >> t1;
    } else {
        cout << "Enter x1: " << endl;
        cin >> x1;     
    }

    //initialize other variables for signal 1

    double wavelength1=speedofLight/fre1;
    double angfre1=2*PI*fre1;
    double wavenum1=(2*PI)/wavelength1;


    //input variables for signal 2 
    double amp2, fre2, iniphase2, t2 = 0, x2 = 0;  
    string test2;  

    cout << "For signal 2 enter the following values: " << endl;

    cout << "Amplitude in volts: " << endl;
    cin >> amp2;
    cout << "Frequency in radians: " << endl;
    cin >> fre2;
    cout << "Initial phase in radians: " << endl;
    cin >> iniphase2;
    
    cout << "Do you want to input t2 or x2? " << endl;
    cin >> test2;  

    if (test2 == "t2") {
        cout << "Enter t2: " << endl;
        cin >> t2;
    } else {
        cout << "Enter x2: " << endl;
        cin >> x2;     
    }

    //initialize other variables for signal 2

    double wavelength2=speedofLight/fre2;
    double angfre2=2*PI*fre2;
    double wavenum2=(2*PI)/wavelength2;

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
    FILE* gnuplotPipe = _popen("C:\\\"Program Files\"\\gnuplot\\bin\\gnuplot.exe", "w");;
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
