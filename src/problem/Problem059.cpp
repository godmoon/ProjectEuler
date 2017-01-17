// XOR decryption
// Problem 59
// Published on 19 December 2003 at 06:00 pm[Server Time]
//
// Each character on a computer is assigned a unique code and the preferred standard is ASCII(American Standard Code for Information Interchange).For example, uppercase A = 65, asterisk(*) = 42, and lowercase k = 107.
// A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each byte with a given value, taken from a secret key.The advantage with the XOR function is that using the same encryption key on the cipher text, restores the plain text; for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.
// For unbreakable encryption, the key is the same length as the plain text message, and the key is made up of random bytes.The user would keep the encrypted message and the encryption key in different locations, and without both "halves", it is impossible to decrypt the message.
// Unfortunately, this method is impractical for most users, so the modified method is to use a password as a key.If the password is shorter than the message, which is likely, the key is repeated cyclically throughout the message.The balance for this method is using a sufficiently long password key for security, but short enough to be memorable.
// Your task has been made easy, as the encryption key consists of three lower case characters.Using cipher1.txt(right click and 'Save Link/Target As...'), a file containing the encrypted ASCII codes, and the knowledge that the plain text must contain common English words, decrypt the message and find the sum of the ASCII values in the original text.
// 
// 题目59：使用暴力攻击，你能解开这个异或加密吗？
// 
// 电脑上的每个字符都有一个唯一编码，通用的标准是ASCII(American Standard Code for Information Interchange 美国信息交换标准编码)。例如大写A = 65， 星号(*) = 42，小写k = 107。
// 一种现代加密方法是用一个密钥中的给定值，与一个文本文件中字符的ASCII值进行异或。使用异或方法的好处是对密文使用同样的加密密钥可以得到加密前的内容。例如，65 XOR 42 = 107, 然后 107 XOR 42 = 65。
// 对于不可攻破的加密，密钥的长度与明文信息的长度是一样的，而且密钥是由随机的字节组成的。用户将加密信息和加密密钥保存在不同地方，只有在两部分都得到的情况下，信息才能被解密。
// 不幸的是，这种方法对于大部分用户来说是不实用的。所以一种修改后的方案是使用一个密码作为密钥。如果密码比信息短，那么就将其不断循环直到明文的长度。平衡点在于密码要足够长来保证安全性，但是又要足够短使用户能够记得。
// 你的任务很简单，因为加密密钥是由三个小写字母组成的。文件 cipher1.txt(右键另存为)包含了加密后的ASCII码，并且已知明文是由常用英语单词组成。使用该文件来解密信息，然后算出明文中字符的ASCII码之和。

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 59

#include <Template.h>

#include <vector>

#include <CppArray.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    // 密文
    uint8_t ARRAY[] = {79, 59, 12, 2, 79, 35, 8, 28, 20, 2, 3, 68, 8, 9, 68, 45, 0, 12, 9, 67, 68, 4, 7, 5, 23, 27, 1, 21, 79, 85, 78, 79, 85, 71, 38, 10, 71, 27, 12, 2, 79, 6, 2, 8, 13, 9, 1, 13, 9, 8, 68, 19, 7, 1, 71, 56, 11, 21, 11, 68, 6, 3, 22, 2, 14, 0, 30, 79, 1, 31, 6, 23, 19, 10, 0, 73, 79, 44, 2, 79, 19, 6, 28, 68, 16, 6, 16, 15, 79, 35, 8, 11, 72, 71, 14, 10, 3, 79, 12, 2, 79, 19, 6, 28, 68, 32, 0, 0, 73, 79, 86, 71, 39, 1, 71, 24, 5, 20, 79, 13, 9, 79, 16, 15, 10, 68, 5, 10, 3, 14, 1, 10, 14, 1, 3, 71, 24, 13, 19, 7, 68, 32, 0, 0, 73, 79, 87, 71, 39, 1, 71, 12, 22, 2, 14, 16, 2, 11, 68, 2, 25, 1, 21, 22, 16, 15, 6, 10, 0, 79, 16, 15, 10, 22, 2, 79, 13, 20, 65, 68, 41, 0, 16, 15, 6, 10, 0, 79, 1, 31, 6, 23, 19, 28, 68, 19, 7, 5, 19, 79, 12, 2, 79, 0, 14, 11, 10, 64, 27, 68, 10, 14, 15, 2, 65, 68, 83, 79, 40, 14, 9, 1, 71, 6, 16, 20, 10, 8, 1, 79, 19, 6, 28, 68, 14, 1, 68, 15, 6, 9, 75, 79, 5, 9, 11, 68, 19, 7, 13, 20, 79, 8, 14, 9, 1, 71, 8, 13, 17, 10, 23, 71, 3, 13, 0, 7, 16, 71, 27, 11, 71, 10, 18, 2, 29, 29, 8, 1, 1, 73, 79, 81, 71, 59, 12, 2, 79, 8, 14, 8, 12, 19, 79, 23, 15, 6, 10, 2, 28, 68, 19, 7, 22, 8, 26, 3, 15, 79, 16, 15, 10, 68, 3, 14, 22, 12, 1, 1, 20, 28, 72, 71, 14, 10, 3, 79, 16, 15, 10, 68, 3, 14, 22, 12, 1, 1, 20, 28, 68, 4, 14, 10, 71, 1, 1, 17, 10, 22, 71, 10, 28, 19, 6, 10, 0, 26, 13, 20, 7, 68, 14, 27, 74, 71, 89, 68, 32, 0, 0, 71, 28, 1, 9, 27, 68, 45, 0, 12, 9, 79, 16, 15, 10, 68, 37, 14, 20, 19, 6, 23, 19, 79, 83, 71, 27, 11, 71, 27, 1, 11, 3, 68, 2, 25, 1, 21, 22, 11, 9, 10, 68, 6, 13, 11, 18, 27, 68, 19, 7, 1, 71, 3, 13, 0, 7, 16, 71, 28, 11, 71, 27, 12, 6, 27, 68, 2, 25, 1, 21, 22, 11, 9, 10, 68, 10, 6, 3, 15, 27, 68, 5, 10, 8, 14, 10, 18, 2, 79, 6, 2, 12, 5, 18, 28, 1, 71, 0, 2, 71, 7, 13, 20, 79, 16, 2, 28, 16, 14, 2, 11, 9, 22, 74, 71, 87, 68, 45, 0, 12, 9, 79, 12, 14, 2, 23, 2, 3, 2, 71, 24, 5, 20, 79, 10, 8, 27, 68, 19, 7, 1, 71, 3, 13, 0, 7, 16, 92, 79, 12, 2, 79, 19, 6, 28, 68, 8, 1, 8, 30, 79, 5, 71, 24, 13, 19, 1, 1, 20, 28, 68, 19, 0, 68, 19, 7, 1, 71, 3, 13, 0, 7, 16, 73, 79, 93, 71, 59, 12, 2, 79, 11, 9, 10, 68, 16, 7, 11, 71, 6, 23, 71, 27, 12, 2, 79, 16, 21, 26, 1, 71, 3, 13, 0, 7, 16, 75, 79, 19, 15, 0, 68, 0, 6, 18, 2, 28, 68, 11, 6, 3, 15, 27, 68, 19, 0, 68, 2, 25, 1, 21, 22, 11, 9, 10, 72, 71, 24, 5, 20, 79, 3, 8, 6, 10, 0, 79, 16, 8, 79, 7, 8, 2, 1, 71, 6, 10, 19, 0, 68, 19, 7, 1, 71, 24, 11, 21, 3, 0, 73, 79, 85, 87, 79, 38, 18, 27, 68, 6, 3, 16, 15, 0, 17, 0, 7, 68, 19, 7, 1, 71, 24, 11, 21, 3, 0, 71, 24, 5, 20, 79, 9, 6, 11, 1, 71, 27, 12, 21, 0, 17, 0, 7, 68, 15, 6, 9, 75, 79, 16, 15, 10, 68, 16, 0, 22, 11, 11, 68, 3, 6, 0, 9, 72, 16, 71, 29, 1, 4, 0, 3, 9, 6, 30, 2, 79, 12, 14, 2, 68, 16, 7, 1, 9, 79, 12, 2, 79, 7, 6, 2, 1, 73, 79, 85, 86, 79, 33, 17, 10, 10, 71, 6, 10, 71, 7, 13, 20, 79, 11, 16, 1, 68, 11, 14, 10, 3, 79, 5, 9, 11, 68, 6, 2, 11, 9, 8, 68, 15, 6, 23, 71, 0, 19, 9, 79, 20, 2, 0, 20, 11, 10, 72, 71, 7, 1, 71, 24, 5, 20, 79, 10, 8, 27, 68, 6, 12, 7, 2, 31, 16, 2, 11, 74, 71, 94, 86, 71, 45, 17, 19, 79, 16, 8, 79, 5, 11, 3, 68, 16, 7, 11, 71, 13, 1, 11, 6, 1, 17, 10, 0, 71, 7, 13, 10, 79, 5, 9, 11, 68, 6, 12, 7, 2, 31, 16, 2, 11, 68, 15, 6, 9, 75, 79, 12, 2, 79, 3, 6, 25, 1, 71, 27, 12, 2, 79, 22, 14, 8, 12, 19, 79, 16, 8, 79, 6, 2, 12, 11, 10, 10, 68, 4, 7, 13, 11, 11, 22, 2, 1, 68, 8, 9, 68, 32, 0, 0, 73, 79, 85, 84, 79, 48, 15, 10, 29, 71, 14, 22, 2, 79, 22, 2, 13, 11, 21, 1, 69, 71, 59, 12, 14, 28, 68, 14, 28, 68, 9, 0, 16, 71, 14, 68, 23, 7, 29, 20, 6, 7, 6, 3, 68, 5, 6, 22, 19, 7, 68, 21, 10, 23, 18, 3, 16, 14, 1, 3, 71, 9, 22, 8, 2, 68, 15, 26, 9, 6, 1, 68, 23, 14, 23, 20, 6, 11, 9, 79, 11, 21, 79, 20, 11, 14, 10, 75, 79, 16, 15, 6, 23, 71, 29, 1, 5, 6, 22, 19, 7, 68, 4, 0, 9, 2, 28, 68, 1, 29, 11, 10, 79, 35, 8, 11, 74, 86, 91, 68, 52, 0, 68, 19, 7, 1, 71, 56, 11, 21, 11, 68, 5, 10, 7, 6, 2, 1, 71, 7, 17, 10, 14, 10, 71, 14, 10, 3, 79, 8, 14, 25, 1, 3, 79, 12, 2, 29, 1, 71, 0, 10, 71, 10, 5, 21, 27, 12, 71, 14, 9, 8, 1, 3, 71, 26, 23, 73, 79, 44, 2, 79, 19, 6, 28, 68, 1, 26, 8, 11, 79, 11, 1, 79, 17, 9, 9, 5, 14, 3, 13, 9, 8, 68, 11, 0, 18, 2, 79, 5, 9, 11, 68, 1, 14, 13, 19, 7, 2, 18, 3, 10, 2, 28, 23, 73, 79, 37, 9, 11, 68, 16, 10, 68, 15, 14, 18, 2, 79, 23, 2, 10, 10, 71, 7, 13, 20, 79, 3, 11, 0, 22, 30, 67, 68, 19, 7, 1, 71, 8, 8, 8, 29, 29, 71, 0, 2, 71, 27, 12, 2, 79, 11, 9, 3, 29, 71, 60, 11, 9, 79, 11, 1, 79, 16, 15, 10, 68, 33, 14, 16, 15, 10, 22, 73};

    /* 加解密 */
    string EncDec(const char *array, uint32_t arrayLen, const string &key)
    {
        string result;

        if (array == NULL)
        {
            return result;
        }

        if (key.empty())
        {
            result.assign(array, arrayLen);
            return result;
        }

        string::const_iterator keyIt = key.begin();
        for (uint32_t i = 0; i < arrayLen; ++i, ++keyIt)
        {
            if (keyIt == key.end())
            {
                keyIt = key.begin();
            }

            result += array[i] ^ (*keyIt);
        }

        return result;
    }
}

using namespace GET_NAMESPACE_NAME(PROBLEM_NO);

/* 当前页面的构造函数，会在页面加载前调用，未请求的页面不会调用 */
GET_CLASS_NAME(PROBLEM_NO)::GET_CLASS_NAME(PROBLEM_NO)() : Problem()
{
    /* TODO */
}

/* 运行 */
string GET_CLASS_NAME(PROBLEM_NO)::Run()
{
    // 思路是：
    // 既然明文是3个小写字母组成，那么先找出所有的可能

    const uint32_t KEY_LEN = 3;     // 密钥长度
    string possbleChar[KEY_LEN];    // 密钥不同位可能的字符
    string skipChar = "{}[]#%`";    // 排除字符串，如果解析出来的文本中含有这些串，则直接放弃

    for (uint32_t i = 0; i < KEY_LEN; ++i)
    {
        for (uint8_t k = 'a'; k <= 'z'; ++k)
        {
            bool isOk = true;
            for (uint32_t c = i; c < ARRAY_SIZE(ARRAY); c += KEY_LEN)
            {
                uint8_t out = k^ARRAY[c];

                // 空格或者字母，表示OK， 否则跳出
                if (!isprint(out) || skipChar.find(out) != string::npos)
                {
                    isOk = false;
                    break;
                }
            }

            if (isOk)
            {
                possbleChar[i] += k;
            }
        }
    }

    for (uint32_t i = 0; i < KEY_LEN; ++i)
    {
        cout << CppString::GetArgs("Possible[%u]=%s\n", i, possbleChar[i].c_str());
        if (possbleChar[i].empty())
        {
            cout << "无结果" << endl;
            return CppString::ToString(-1);
        }
    }

    // 解密，得到所有的组合，并且人工判断结果合法性，排除一些差异，添加到skipChar使得结果更加准确
    string resultText;
    string key;

    for (string::const_iterator kIt0 = possbleChar[0].begin(); kIt0 != possbleChar[0].end(); ++kIt0)
    {
        for (string::const_iterator kIt1 = possbleChar[1].begin(); kIt1 != possbleChar[1].end(); ++kIt1)
        {
            for (string::const_iterator kIt2 = possbleChar[2].begin(); kIt2 != possbleChar[2].end(); ++kIt2)
            {
                key = string() + *kIt0 + *kIt1 + *kIt2;
                resultText = EncDec((char *)ARRAY, ARRAY_SIZE(ARRAY), key);
                cout << CppString::GetArgs("key[%s],result[%s].\n", key.c_str(), resultText.c_str());
            }
        }
    }

    uint32_t sum = 0;
    for (string::const_iterator rIt = resultText.begin(); rIt != resultText.end(); ++rIt)
    {
        sum += *rIt;
    }

    return CppString::ToString(sum);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
./ProjectEuler 59
[2014-07-19 14:38:52.477524]开始运行第59题
Possible[0]=g
Possible[1]=o
Possible[2]=d
key[god],result[(The Gospel of John, chapter 1) 1 In the beginning the Word already existed. He was with God, and he was God. 2 He was in the beginning with God. 3 He created everything there is. Nothing exists that he didn't make. 4 Life itself was in him, and this life gives light to everyone. 5 The light shines through the darkness, and the darkness can never extinguish it. 6 God sent John the Baptist 7 to tell everyone about the light so that everyone might believe because of his testimony. 8 John himself was not the light; he was only a witness to the light. 9 The one who is the true light, who gives light to everyone, was going to come into the world. 10 But although the world was made through him, the world didn't recognize him when he came. 11 Even in his own land and among his own people, he was not accepted. 12 But to all who believed him and accepted him, he gave the right to become children of God. 13 They are reborn! This is not a physical birth resulting from human passion or plan, this rebirth comes from God.14 So the Word became human and lived here on earth among us. He was full of unfailing love and faithfulness. And we have seen his glory, the glory of the only Son of the Father.].
[2014-07-19 14:38:52.478070]第59题运行完毕，结果[107359]: From start 546 us,from last 546 us
By Moon
*/
