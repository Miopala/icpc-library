vector<int> matches(string text, string pattern)
{
    vector<Complex<long double>> textPolynomial, patternPolynomial;
    long double alpha;
    long double PI = acos(-1);
    
    int wildcardCount = 0;

    for(char c : text){
        alpha = 2 * PI * (c - 'A') / 2;
        textPolynomial.emplace_back(cosl(alpha), sinl(alpha));
    }

    for (int i = pattern.length() - 1; i >= 0; --i)
    {
        char c = pattern[i];
        if (c == '?')
        {
            ++wildcardCount;
            patternPolynomial.emplace_back(0, 0);
        }
        else
        {
            alpha = 2 * PI * (c - 'A') / 2;
            patternPolynomial.emplace_back(cosl(alpha), -sinl(alpha));
        }
    }

    vector<Complex<long double>> c = multiplyPolynomials(textPolynomial, patternPolynomial);

    vector<int> result;

    for(int i = pattern.length() - 1; i < c.size(); ++i) if(isEqual(c[i], pattern.length() - wildcardCount)) result.push_back(i - pattern.length() + 1);

    return result;
}