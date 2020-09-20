#include "Parse.h"

///@brief Find number in string. Inlcuding hex, binary, octal
///@tparam T is the number type. Either size_t, Binary, Hex, or Octal
///@param x String to look in
///@param pos The index in string to start searching beyond
///@return Index of cloesest number found
template <typename T>
size_t Parse::FindNumber(std::string x, size_t pos)
{
    std::vector<size_t> numbers = std::vector<size_t>();

    if(typeid(T) == typeid(size_t))
    {
        numbers.push_back(x.find('0', pos));
        numbers.push_back(x.find('1', pos));
        numbers.push_back(x.find('2', pos));
        numbers.push_back(x.find('3', pos));
        numbers.push_back(x.find('4', pos));
        numbers.push_back(x.find('5', pos));
        numbers.push_back(x.find('6', pos));
        numbers.push_back(x.find('7', pos));
        numbers.push_back(x.find('8', pos));
        numbers.push_back(x.find('9', pos));
    }
    else if(typeid(T) == typeid(Numbers::Hex))
    {
        numbers.push_back(x.find("0x", pos));
    }

    //
    size_t index_of_closest_num = std::string::npos;
    for(int i = 0; i < numbers.size(); i++)
    {
        if(numbers[i] < index_of_closest_num)
        {
            index_of_closest_num = numbers[i];
        }
    }

    return index_of_closest_num;
}

float Parse::Normalize(int num, int low, int high)
{
    float range = high - low;
    if(num > range)
    {
        return num / (high + low);
    }
    
    if(num <= range)
    {
        return num / (range);
    }

    return 0;
}

///@brief Parses model file to a VertexBuffer
///@param file_path The file path to the model file
///@return A pointer to VertexBuffer object
std::shared_ptr<Graphics::VertexBuffer> Parse::FileToVbo(std::string file_path)
{
    //{{x, y, z}, {r, g, b, a}},

    std::vector<Graphics::Vertex> vertices = std::vector<Graphics::Vertex>();
    std::string file_contents = File::ReadFile(file_path);

    size_t i = FindNumber<size_t>(file_contents, 0); //find closest single digit
    
    //Return nullptr if no number is found
    if(i == std::string::npos)
    {
        return nullptr;
    }

    enum Attributes
    {
        X, Y, Z,
        R, G, B, A
    };

    enum NumberBase
    {
        DECIMAL, HEX, BINARY, OCTAL
    };

    Graphics::Vector3 vec3 = Graphics::Vector3();
    Graphics::Color color = Graphics::Color();
    Attributes current_attribute = X;


    size_t begin = i; //beginning of string for substr()

    //Keep track of number being negative or not
    bool num_is_neg = false;
    if(file_contents[i - 1] == '-')
    {
        num_is_neg = true;
    }

    NumberBase base = DECIMAL;
    while(i < file_contents.size() || i != std::string::npos)
    {
        if(file_contents[i] == ',' || file_contents[i] == '}')
        {
            if(num_is_neg)
            {
                begin--;
            }

            float num;

            //Substring to number
            switch(base)
            {
                case DECIMAL:
                    num = std::stod(file_contents.substr(begin, i - begin));
                    break;
                case HEX:
                    num = Normalize(Numbers::Hex(file_contents.substr(begin, i - begin)).ToDecimal(), 0, 255);
                    break;
                case BINARY:
                    num = Normalize(Numbers::Binary(file_contents.substr(begin, i - begin)).ToDecimal(), 0, 255);
                    break;
            }

            switch(current_attribute)
            {
                case X:
                    vec3.x = num;
                    current_attribute = Y;
                    break;
                case Y:
                    vec3.y = num;
                    current_attribute = Z;
                    break;
                case Z:
                    vec3.z = num;
                    current_attribute = R;
                    break;
                case R:
                    color.r = num;
                    current_attribute = G;
                    break;
                case G:
                    color.g = num;
                    current_attribute = B;
                    break;
                case B:
                    color.b = num;
                    current_attribute = A;
                    break;
                case A:
                    color.a = num;
                    vertices.push_back(Graphics::Vertex(vec3, color));

                    //Reset vec3 and color for next vertex
                    vec3.x = 0;
                    vec3.y = 0;
                    vec3.z = 0;
                    
                    color.r = 0;
                    color.g = 0;
                    color.b = 0;
                    color.a = 0;

                    current_attribute = X;
                    break;
            }

            //Finds next number
            size_t next_decimal = FindNumber<size_t>(file_contents, i);
            size_t next_hex = FindNumber<Numbers::Hex>(file_contents, i);
            if(next_decimal < next_hex)
            {
                i = next_decimal;
                base = DECIMAL;
            }
            else
            {
                i = next_hex;
                base = HEX;
            }

            if(i == std::string::npos)
            {
                break;
            }
            begin = i;
            
            if(file_contents[i - 1] == '-')
            {
                num_is_neg = true;
            }
            else
            {
                num_is_neg = false;
            }
        }
        i++;
    }

    std::shared_ptr<Graphics::VertexBuffer> vbo = std::make_shared<Graphics::VertexBuffer>(vertices);
    return vbo;
}