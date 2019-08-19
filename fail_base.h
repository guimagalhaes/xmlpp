#ifndef FAIL_BASEH_
#define FAIL_BASEH_

class fail_base
{
    private:
        bool _fail;
        int _err;
    
    public:
        fail_base(): _fail(false), _err(0) {}
        virtual ~fail_base() {}
    
        void set_failed(bool b = true) { _fail = b; }
        
        //return true if some error occur
        bool failed() {if (_fail) {clear_error(); return true;} return false;}
        //clear error number, failed will return false
        void clear_error() {_err = 0; _fail = false; }
        
        //get and set error number
        int get_error_number() const {return _err;}
        void set_error_number(int value) {_err = value; set_failed(); }
};

#endif
