# Password-Policies

In the new web application you have developed, it is necessary to introduce additional security elements. For this, you will develop a library of Password Policies. These password policies are configured by each client using your library, and then each password set by users is checked against these rules. They are:

Length - the restriction can specify the minimum length or both the minimum and maximum length of a password.
Class - the restriction states how many different classes of characters the password must have at least; the classes are: lowercase letter, uppercase letter, digit, and other characters.
Must Include - the password must include at least one character from the specified class.
Must Not Include - the password must not include any character from the specified class.
Repetition - the restriction specifies how many times the same character can be repeated consecutively in the password.
Consecutive - the restriction imposes a maximum number of consecutive characters (e.g., abc or 123).


Task:
Given a set of secure password policies and a list of passwords, display OK or NOK for each of them, depending on whether all of these policies are met or not.

Input:
The first line contains a positive integer n, an unknown but not very large number, representing the number of rules to be followed. The next n lines contain the definition of a rule, in the following possible formats:

length <min_length> - the password must have min_length characters (inclusive); 0 < min_length
length <min_length> <max_length> - the password must have between min_length and max_length characters (inclusive); 0 < min_length <= max_length
class <min_class_count> - the password must have at least min_class_count different types of characters (lowercase letter, uppercase letter, digit, and other characters); 0 < min_class_count < 5
include <class> - the password must include at least one character from the specified class; class can be a, A, 0, or $, denoting the desired class
ninclude <class> - the password must not include any character from the specified class; class follows the same rules as above
repetition <max_count> - the same character can be repeated consecutively for a maximum of max_count times; 0 < max_count
consecutive <max_count> - the password can have a maximum of max_count consecutive characters in a sequence; 0 < max_count
The following lines, until EOF, contain one password per line, which will be checked against the specified rules.

Output:
For each checked password, display OK if the password meets ALL the specified rules, or NOK if there is at least one rule that is not met.
