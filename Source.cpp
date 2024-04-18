#include <iostream>
#include <vector>
#include <unordered_map>

int least_recently_used(const std::vector<int>& page_reference, int num_frames) {
    std::unordered_map<int, int> table; //usde to track current pages in memory
    std::vector<int> frames;
    int faults = 0;

    for (int page : page_reference) {
        if (table.find(page) != table.end()) { //page hit scenario, when find does not return end
            auto it = find(frames.begin(), frames.end(), page);
            frames.erase(it);
            frames.push_back(page); // makes it the most recently used
        }
        else { //miss scenario, replacement page fault
            faults++;
            std::cout << "Page fault at: " << page << ", total faults " << faults << std::endl;
            if (frames.size() == num_frames) { //checks if frame is full, error handling
                int least_ru_page = frames.front();
                frames.erase(frames.begin()); //kills the frame
                table.erase(least_ru_page); //kills the table
            }
            // inits new page
            frames.push_back(page);
            // Update the page table with the new page
            table[page] = 1;
        }
    }
    return faults;
}

int optimal(const std::vector<int>& page_reference, int num_frames) {
    std::unordered_map<int, int> table;
    std::vector<int> frames;
    int faults = 0;

    for (int page : page_reference) {
        //int page = page_reference[i];
        if (table.find(page) != table.end()) {// page hit
            continue;
        }
        
        else {// page miss
            faults++; // increment page fault counter
            std::cout << "Page fault at: " << page << ", total faults " << faults << std::endl;
            if (frames.size() == num_frames) {//checks if all frames full
                int index = -1, farthest = -1; //optimal algorithim
                for (int j = 0; j < frames.size(); ++j) {//the furtherest one away is typically seen as the one that wont be used
                    int next_index = page + 1;
                    while (next_index < page_reference.size()) {
                        if (page_reference[next_index] == frames[j]) {
                            if (next_index > farthest) {
                                farthest = next_index;
                                index = j;
                            }
                            break;
                        }
                        next_index++;
                    }
                    if (next_index == page_reference.size()) {
                        index = j;
                        break;
                    }
                }
                table.erase(frames[index]); //kill the furthest page
                frames[index] = page;
            }
            else {
                // Add the new page to the frames
                frames.push_back(page);
            }
            // Update the page table with the new page
            table[page] = 1;
        }
    }

    return faults;
}

int fifo(const std::vector<int>& page_reference, int num_frames) {
    std::unordered_map<int, int> table;
    std::vector<int> frames;
    int faults = 0;
        for (int page : page_reference){
            if (table.find(page) != table.end()) {// page hit
                continue;
            }
            else {
                faults++; //case if pages are full
                std::cout << "Page fault at: " << page << ", total faults " << faults << std::endl;
                if (frames.size() == num_frames) {
                    int killed = frames.front(); //targets oldest
                    frames.pop_back();
                    table.erase(killed);//remove the oldest page from the page table

                }
                frames.push_back(page);
                table[page] = true;//new page
            }
            }

        return faults;
    }
   
int main() {
    std::vector<int> page_reference = { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 };// sample references
    int num_frames = 4;
    std::cout << "LRU implementation: " << std::endl << std::endl;
    least_recently_used(page_reference, num_frames);
    std::cout << std::endl << "OPTIMAL implementation: " << std::endl << std::endl;;
    optimal(page_reference, num_frames);
    std::cout << std::endl << "FIFO implementation: " << std::endl << std::endl;
    fifo(page_reference, num_frames);
    return 0;
}