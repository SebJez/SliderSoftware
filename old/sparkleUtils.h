#ifndef sparkleUtils_h
#define sparkleUtils_h

typedef uint8_t pin;

namespace sparkle
{
    template<class integer_t> 
    String formatInteger(integer_t value,byte decimal_places = 0, bool use_plus_sign = false, \
                                    String prefix = "", String postfix = "");

    template<class float_t>
    String formatFloatingPoint(float_t value, byte decimal_places, bool use_plus_sign = false, \
                                    String prefix = "", String postfix = "");


    inline String padString(String string_to_pad, byte target_length, byte split_position = 0);

}

String sparkle::formatInteger(integer_t value,byte decimal_places = 0, bool use_plus_sign = false,\
                                     String prefix = "", String postfix = "")
{
    String number = String(abs(value));

    while(number.length() <= decimal_places) number = "0" + number;
    
    if(use_plus_sign)
        String sign = (value < 0) ? "-" : "+";
    else
        String sign = (value < 0) ? "-" : "";

    String separator = (decimal_places > 0) ? "." : "";

    byte len = number.length();

    return prefix + sign + number.substring(0,len-decimal_places) + \
            separator + number.substring(len-decimal_places,len) + postfix;
    
}

String sparkle::formatFloatingPoint(float_t value, byte decimal_places, bool use_plus_sign = false, \
                                    String prefix = "", String postfix = "")
{
    String number = String(value,decimal_places);
    if (use_plus_sign && value >= 0) number = "+" + number;

    return prefix + number + postfix;
}

String sparkle::padString(String string_to_pad, byte target_length, byte split_position = 0)
{
    while(string_to_pad.length() < target_length)
        string_to_pad =string_to_pad.substring(0,split_position) " " + string_to_pad.substring(split_position);
    return string_to_pad;
}


#endif