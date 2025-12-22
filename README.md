SIMPLE CLI TO-DO APPLICATION

## Features
- Add an item
    - task title, task description
- Delete an item
- Modify an item
- Mark the item as done
- Exit the program
- Two sections:
    - Pending
    - Done

## How it works
- Upon app start
    - Datafiles existance is checked
        - Datafile is created upon first start
        - Data is stored in .psv ("pipe separated file"), one item per record.
    - The whole datafile is read to the program (for fast use)
- The main loop
    - UI shows the sections 'pending' and 'done'
        - id and title is shown for every item
    - Prompt user for an action and wait until one is given
        - ADD, add an item
        - DEL \<id>, delete an item
        - MOD \<id>, modify an existing item,
        - FIN \<id>, mark item as finished
        - SAVE, saves the work to the file -> no autosave
        - EXIT, exit the program
    - if given action is valid behave accordingly
        - if action is not valid give an explicit error and show help and return loop beginning

- User adds an item (ADD)
    - Item title and description is prompted from the user
        - max chars is set for title to keep the UI clean
        - max chars is currently set for the description to keep implemenation simple
    - Item gets an id and it is saved to the datafile
        - Also keep it in program memory so it doesn't need to be read from the datafile again under current session
    - UI presents the new item on PENDING section
- User deletes an item (DEL)
    - Item is removed from the datafile and programs memory all together
    - Item's id is freed for future use (might be tricky)
        Consider: id's are unique and never reused withing a datafile
- Modify an item (MOD)
    - User selects an id to modify
    - Description of the item is shown to the user
        - For now everything will be overwritten. Later a partial modification should be added.
    - re-prompt title and description
- User marks item as done (FIN)
    - Item is moved from PENDING to DONE section
    - Item's id is still preserved for possible deleting

## Ideas
- Every item could be a struct, with uint id, char title[20], char \*description, enum status (pending/done).
- All the structs should be adjacent in memory
    - allocate some extra structs at the beginning of session
    - and/or use realloc
- When program is running DEL will set the item-\>id to 0.
    - When the program exits items with id 0 will not be written to the file
    - i.e. DEL will not remove anything during program running
- It probably doesn't make any sense to write the id to the file.
    - Remove and change the initiali datafile reading.
    
## Approach and what I'm currently working on
OK=section done, WIP=currently working on, NO=not yet started
1. OK Define structs and enums
2. OK Implement in-memory storage
3. OK Add / delete / modify without file I/O
4. OK Add file load/save
5. OK Add command parsing
6. NO Polish error handling

## Error handling
- Make sure the user can't add pipe "|" character
- Check every memory allocation failure
- Make a temp file where data will be written
    - When writing is done successfully -> delete the old file
- OK Prompt the user that max length of title is 15 and if it's longer, it will be truncated.
    - OK Same thing for the description
- OK Prevent empty title (description can be empty).

## Features to add
- Due date
    - new section for "due date missed"
    - prompt user for due date
        - Error handling is needed for date validation
    - check all the due dates when app is started
    - allow due date modification
        check if item needs to be moved from due date missed to pending
- add possibility to modify the items without overwriting.
    - If I do the text editor I would know how
- "unlimited" size description (The title should always be limited)
- user could also provide a datafile as an argument.
    - Or user could load it inside the program LOAD \<datatfile>
- termios.h for the control character usage
    - atl+\n will give new line on description

## What is currently missing
- No due date
- No undo/redo
- No concurrent access
- No partial text editing
