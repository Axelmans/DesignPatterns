//
// Created by axelmans on 2/09/23.
//

#include <iostream>
#include <memory>

using namespace std;

namespace CommandPattern{

    /*
     * Command interface.
     */
    struct Command{
        virtual void execute() = 0;
        virtual ~Command() = default;
    };

    /*
     * Dualsense = PS5 Controller;
     * It has a joystick that can be moved and an X button to press.
     */
    struct Dualsense{
        static void pressX() {
            cout << "Pressed the X button.\n";
        }
        static void moveJoystick(){
            cout << "Moved the joystick.\n";
        }
        ~Dualsense() = default;
    };

    /*
     * Concrete commands to do either or.
     */
    struct XPress: Command{
        unique_ptr<Dualsense> connected_controller = make_unique<Dualsense>();
        void execute() override {
            connected_controller->pressX();
        }
        ~XPress() override = default;
    };

    struct Mover: Command{
        unique_ptr<Dualsense> connected_controller = make_unique<Dualsense>();
        void execute() override {
            connected_controller->moveJoystick();
        }
        ~Mover() override = default;
    };

    /*
     * The user/player is the invoker that presses buttons.
     */
    struct User{
        unique_ptr<Command> to_be_executed = nullptr;
        void setCommand(unique_ptr<Command>& c){
            to_be_executed = std::move(c);
        }
        void press() const {
            to_be_executed->execute();
        }
    };

    /*
     * Test scenario.
     */
    static int main(){
        unique_ptr<Command> m(new Mover);
        unique_ptr<Command> x(new XPress);
        unique_ptr<User> u(new User);
        u->setCommand(m);
        u->press(); // Moved the joystick.
        u->setCommand(x);
        u->press(); // Pressed the X button.
        return 0;
    }

}