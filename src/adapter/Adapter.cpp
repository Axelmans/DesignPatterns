//
// Created by axelmans on 1/09/23.
//

#include <iostream>
#include <memory>
using namespace std;

/*
 * Adapter Pattern: Make 2 incompatible interfaces compatible by an Adapter interface.
 */

/*
 * EXAMPLE: Switching from UDP application to TCP application.
 */

namespace Adapter {

    /*
     * UDP interface and a concrete UDP application.
     */
    struct UDP {
        virtual void sendPacket() = 0;
        virtual ~UDP() = default;
    };

    struct Skype: UDP {
        void sendPacket() override {
            cout << "Sending UDP packet...\nStarting services...\n" << endl;
        }
        ~Skype() override = default;
    };

    /*
     * TCP interface and a concrete TCP application.
     */
    struct TCP {
        virtual void establishConnection() = 0;
        virtual ~TCP() = default;
    };

    struct Whatsapp : TCP {
        void establishConnection() override {
            cout << "Initiating TCP connection...\n"
                    "Sending TCP synchronize, waiting for syn-acknowledgement...\n"
                    "Acknowledgement received, sending final acknowledgement!\n"
                    "Starting services...\n" << endl;
        }
        ~Whatsapp() override = default;
    };

    /*
     * Adapter class: it should inherit from one interface and contain an object
     * of the other interface.
     */
    struct UDPtoTCP : UDP {
    public:
        // Method should have names from interface of which is inherited.
        void sendPacket() override {
            cout << "Converting UDP datagram to TCP datagram...\n";
            B->establishConnection();
        }
        ~UDPtoTCP() override = default;
    private:
        unique_ptr<TCP> B{new Whatsapp};
    };

    // Scenario to run.
    static int main() {
        unique_ptr<UDP> s_udp(new Skype);
        unique_ptr<TCP> w_tcp(new Whatsapp);
        unique_ptr<UDP> u_t(new UDPtoTCP);
        s_udp->sendPacket(); // Should print UDP message
        w_tcp->establishConnection(); // Should print TCP message
        u_t->sendPacket(); // Should print TCP message
        return 0;
    }

}