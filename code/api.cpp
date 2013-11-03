//api.cpp - an interface for interacting with the loader

#include "api.h"


vector<string> get_input(void) {

    //send prompt
    cout << ">>>> ";

    //get type of action
    string action;
    cin >> action;

    if (action == "m2p") {
        string x, y, z;
        cin >> x >> y >> z;

        vector<string> out(4);
        out[0] = action;
        out[1] = x;
        out[2] = y;
        out[3] = z;
        return out;
    }

    else if (action == "set_angles") {
        string base, shdr, elbw, wrst;

        cin >> base >> shdr >> elbw >> wrst;

        vector<string> out(5);

        out[0] = action;
        out[1] = base;
        out[2] = shdr;
        out[3] = elbw;
        out[4] = wrst;
        return out;
    }

    else if (action == "cc" || action == "oc" || action == "exit" || \
            action == "h") {

        vector<string> out(1);
        out[0] = action;
        return out;
    }
    else if (action == "mf" || action == "mb" || action == "tl" || \
            action == "tr") {
        string speed;

        cin >> speed;
        vector<string> out(2);
        out[0] = action;
        out[1] = speed;
        return out;
    }

    else {
        cout << "Invalid Command: " << action << endl;
        vector<string> out(1);
        out[0] = "Error";
        return out;
    }
}


void perform_action(Loader loader, vector<string> input) {

    if (input[0] == "exit") {
        exit(0);
    }
    else if (input[0] == "m2p") {
        double x = atof(input[1].c_str());
        double y = atof(input[2].c_str());
        double z = atof(input[3].c_str());

        vector<double> point(3);
        point[0] = x;
        point[1] = y;
        point[2] = z;

        loader.move_to_point(point);
    }

    else if (input[0] == "set_angles") {

        vector<double> angles(4);

        angles[0] = 180.0 - atof(input[1].c_str());
        angles[1] = atof(input[2].c_str());
        angles[2] = 180.0 - atof(input[3].c_str());
        angles[3] = 180.0 - atof(input[4].c_str());

        loader.set_angles(angles);
    }

    else if (input[0] == "cc") {
        loader.close_claw();
    }
    else if (input[0] == "oc") {
        loader.open_claw();
    }
    else if (input[0] == "mf") {
        int speed = atoi(input[1].c_str());

        loader.forward(speed);
    }
    else if (input[0] == "mb") {
        int speed = atoi(input[1].c_str());

        loader.reverse(speed);
    }
    else if (input[0] == "tl") {
        int speed = atoi(input[1].c_str());

        loader.turn_left(speed);
    }
    else if (input[0] == "tr") {
        int speed = atoi(input[1].c_str());

        loader.turn_right(speed);
    }

    else if (input[0] == "Error");

    else if (input[0] == "h") {
        print_help();
    }

}


void print_help(void) {

    cout << "exit -- exits program\n";
    cout << "h -- displays this help\n";
    cout << "m2p x y z -- moves the end effector to point (x, y, z)\n";
    cout << "set_angles base shdr elbw wrst -- sets the joint angles\n";
    cout << "mf speed -- move the loader forward at given speed (0-100)\n";
    cout << "mb speed -- moves the loader backwards at given speed (0-100)\n";
    cout << "tl speed -- turns the loader left at given speed (0-100)\n";
    cout << "tr speed -- turns the loader left at given speed (0--100)\n";
    cout << "cc -- closes the claw\n";
    cout << "oc -- opens the claw\n";
}

int main(int argc, char ** argv) {

    vector<string> input;
    Loader loader = Loader();

    while (1) {

        input = get_input();
        perform_action(loader, input);
    }
    return 0;
}
