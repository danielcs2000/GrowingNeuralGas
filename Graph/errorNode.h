
template <typename N>
class ErroNode {
public:
    ErrorNode() {};
    ErrorNode(N tag, double x, double y, double error): tag(tag), x(x), y(y),error(error) {}
    N getTag () const { return tag; }
    double getX () const { return x; }
    double getY () const { return y; }
    double getError () const {return error;}
    void setX(double x) {this->x = x;}
    void setY(double y) {this->y = y;}
    bool operator < (const ErroNode& other) const { return error <= other.error; }
    bool operator == (const ErrorNode& other) const { return tag == other.tag; }


private:
    N tag;
    double x;
    double y;
    double error;
};
