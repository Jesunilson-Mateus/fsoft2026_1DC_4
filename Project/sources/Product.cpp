// Product class implementation

class Product {
    private:
        std::string name;
        double price;
        int quantity;

    public:
        // Constructor
        Product(std::string name, double price, int quantity) {
            this->name = name;
            this->price = price;
            this->quantity = quantity;
        }

        // Getter methods
        std::string getName() {
            return name;
        }

        double getPrice() {
            return price;
        }

        int getQuantity() {
            return quantity;
        }

        // Method to calculate total price
        double totalPrice() {
            return price * quantity;
        }
};
