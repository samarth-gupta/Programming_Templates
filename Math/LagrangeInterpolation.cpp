// WARNING: depends on Math class
class Lagrange
{
public:
    ll SZ;
    int MODULO;
    Math<ll> m;
    Lagrange(int md = MOD)
    {
        MODULO = md;
    }
    ll interpolate( vector<ll> &ys, ll x )
    {
        SZ = ys.size();
        m = Math<ll>(SZ);

        vector<ll> pref{1};
        for(int i=0;i<SZ;i++)
            pref.pb( mod( pref.back() * (x-i), MODULO ) );
        
        vector<ll> suff{1};
        for(int i=SZ-1;i>=0;i--)
            suff.pb( mod( suff.back() * (x-i), MODULO ) );

        ll ans = 0;
        for(int i=0;i<SZ;i++)
        {
            ll now = ys[i];
            now = mod( now * pref[i], MODULO );
            now = mod( now * suff[SZ-1-i], MODULO );
            now = mod( now * m.invfact[i], MODULO );
            now = mod( now * m.invfact[SZ-1-i], MODULO );

            if( (SZ-1-i)%2 )
                now = mod( -now, MODULO );
            add( ans, now, MODULO );
        }
        return ans;
    }
};