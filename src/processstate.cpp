
#include <common/vtapi_global.h>
#include <data/vtapi_processstate.h>

using std::string;

using namespace vtapi;

static const struct
{
    ProcessState::STATUS_T status;
    const char *str;
}
status_map[] = {
    { ProcessState::STATUS_CREATED,     "created" },
    { ProcessState::STATUS_RUNNING,     "running" },
    { ProcessState::STATUS_SUSPENDED,   "suspended" },
    { ProcessState::STATUS_FINISHED,    "finished" },
    { ProcessState::STATUS_ERROR,       "error" },
    { ProcessState::STATUS_NONE,        NULL },
};



ProcessState::ProcessState()
{
    status = STATUS_NONE;
    progress = 0.0;
}

ProcessState::ProcessState(STATUS_T status, float progress, const std::string& item)
{
    this->status = status;
    this->progress = progress;
    
    if (status == STATUS_RUNNING) {
        this->currentItem = item;
    }
    else {
        this->lastError = item;
    }
}

ProcessState::~ProcessState()
{
}

ProcessState::STATUS_T ProcessState::toStatusValue(const string& status_string)
{
    STATUS_T status = STATUS_NONE;
    
    for (int i = 0; status_map[i].str; i++) {
        if (status_string.compare(status_map[i].str) == 0) {
            status = status_map[i].status;
            break;
        }
    }
    
    return status;
}

string ProcessState::toStatusString(STATUS_T status)
{
    string status_string;

    for (int i = 0; status_map[i].str; i++) {
        if (status == status_map[i].status) {
            status_string = status_map[i].str;
            break;
        }
    }

    return status_string;
}
