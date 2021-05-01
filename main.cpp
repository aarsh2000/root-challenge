#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include <cmath>

using namespace std;

//----------------------------------------------------//
// Driver struct for users                            //
//----------------------------------------------------//
struct Driver
{
private:
    string name;
    double milesDriven;
    double totalDuration;

public:
    Driver(string name)
        : name(name), milesDriven(0), totalDuration(0) {}

    string getName()
    {
        return name;
    }
    double getTotalDuration()
    {
        return totalDuration;
    }
    double getMilesDriven()
    {
        return milesDriven;
    }

    void setMilesDriven(double newMilesDriven)
    {
        milesDriven = newMilesDriven;
    }
    void setTotalDuration(double newTotalDuration)
    {
        totalDuration = newTotalDuration;
    }
};

//---------------------------------------------------------------//
// splits the words in string text and stores it in vector words //
//---------------------------------------------------------------//
void splitText(vector<string> *words, string text)
{
    istringstream iss(text, istringstream::in);
    string word;
    while (iss >> word)
    {
        words->push_back(word);
    }
}

//---------------------------------------------------------------------//
// Takes two 24 hr times and calculates the duration from start to end //
//---------------------------------------------------------------------//
double getDurationInHours(string start, string end)
{
    double NUM_MINUTES_IN_HOUR = 60.0;
    double startHour = stod(start.substr(0, 2));
    double startMinutes = stod(start.substr(3, 5));

    double endHour = stod(end.substr(0, 2));
    double endMinutes = stod(end.substr(3, 5));

    return ((endHour - startHour) * NUM_MINUTES_IN_HOUR + endMinutes - startMinutes) / NUM_MINUTES_IN_HOUR;
}

//----------------------------------------------------//
// main                                               //
//----------------------------------------------------//
int main()
{
    const double MIN_SPEED = 5;
    const double MAX_SPEED = 100;
    map<string, unique_ptr<Driver> > drivers; // use key value pair (kvp) to keep track of drivers where key is name, and value is Driver (struct)
    string text;
    while (getline(cin, text)) // read stdin
    {
        vector<string> words;

        splitText(&words, text);

        if (words[0] == "Driver") // insert new kvp
        {
            drivers.insert({words[1], make_unique<Driver>(words[1])});
        }
        else // insert trip for existing kvp
        {
            Driver *d = drivers.at(words[1]).get();
            const double tripDuration = getDurationInHours(words[2], words[3]);
            const double tripSpeed = stof(words[4]) / tripDuration;
            if (tripSpeed >= MIN_SPEED && tripSpeed <= MAX_SPEED)
            {
                d->setMilesDriven(d->getMilesDriven() + stof(words[4]));
                d->setTotalDuration(d->getTotalDuration() + tripDuration);
            }
        }
    }

    priority_queue<pair<double, unique_ptr<Driver> > > pq; // we use max heap to sort, where key is miles driven, and values is Driver (struct)

    for (auto &it : drivers) // itterate through map kvp
    {
        pq.push(make_pair(it.second->getMilesDriven(), move(it.second))); // insert to max heap
    }

    while (!pq.empty()) // itterate through priority queue kvp and print drivers
    {
        Driver *d = pq.top().second.get();
        if ((d->getMilesDriven()) == 0 || (d->getTotalDuration()) == 0)
        {
            cout << d->getName() << ": 0 miles" << endl;
        }
        else
        {
            const double averageSpeed = d->getMilesDriven() / d->getTotalDuration();
            cout << d->getName() << ": " << round(d->getMilesDriven()) << " miles @ " << round(averageSpeed) << " mph" << endl;
        }
        pq.pop();
    }
}
