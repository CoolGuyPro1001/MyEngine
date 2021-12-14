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
    else if(typeid(T) == typeid(Hex))
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

Level Parse::OpenLevelFile(std::string file_path)
{
    FILE* file;
    file = fopen(file_path.c_str(), "r");
    if(file == NULL)
    {
        printf("Can't open file\n");
        return Level();
    }

    Level lvl = Level();

    //Actors
    u32 actor_buffer_size;
    fread(&actor_buffer_size, sizeof(u32), 1, file);

    int i = 0;
    while(i < actor_buffer_size)
    {
        Shared<Actor> actor = CreateShared<Actor>();

        fread(&actor->position, sizeof(Vector3), 1, file);
        fread(&actor->rotation, sizeof(Vector3), 1, file);
        fread(&actor->scale, sizeof(Vector3), 1, file);

        fread(&actor->position_velocity, sizeof(Vector3), 1, file);
        fread(&actor->rotation_velocity, sizeof(Vector3), 1, file);
        fread(&actor->scale_velocity, sizeof(Vector3), 1, file);

        lvl.actors.push_back(actor);
        i++;
    }


    //Cameras
    char camera_buffer_size;
    fread(&camera_buffer_size, sizeof(u8), 1, file);

    i = 0;
    while(i < camera_buffer_size)
    {
        Camera camera = Camera();
        
        fread(&camera.position, sizeof(Vector3), 1, file);
        fread(&camera.looking_at, sizeof(Vector3), 1, file);
        fread(&camera.focal_distance, sizeof(float), 1, file);
        fread(&camera.velocity, sizeof(Vector3), 1, file);

        lvl.cameras.push_back(camera);
        i++;
    }

    return lvl;
}