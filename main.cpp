#include <stdio.h>
#include <math.h>

void generateChessBoard()
{
    char buf[256];
    for (int i = 0; i < 60; ++i) {
        snprintf(buf, sizeof(buf), "output-%02d.ppm", i);
        const char* output_path = buf;
        FILE *f = fopen(output_path, "wb");
        
        int width = 16 * 60;
        int height = 9 * 60;
        
        fprintf(f, "P6\n");
        fprintf(f, "%d %d\n", width, height);
        fprintf(f, "255\n"); // max bit depth

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {  
                if (((x + i) / 60 + (y + i) / 60) % 2 == 0) { // this will now shift diagonally 
                    fputc(0xFF, f); // full red
                    fputc(0x00, f); // no green for now
                    fputc(0x00, f); // no blue for now
                }
                else {
                    fputc(0x00, f); // full black
                    fputc(0x00, f);
                    fputc(0x00, f);
                }
            }
        }

        fclose(f); // close file
        printf("Generated %s\n", output_path);
    }
}

// forward declarations
struct vec3;
struct vec4;

struct vec2
{
    float x, y;
    vec2(float x = 0, float y = 0):
        x(x), y(y)
    {}

    vec2 yx() const { return vec2(y, x); }
    vec4 xyyx() const;
    vec3 xyy() const;
};

struct vec3
{
    float x, y, z;
    vec3(float x = 0, float y = 0, float z = 0):
        x(x), y(y), z(z)
    {}

    vec2 xy() const { return vec2(x, y); }
    vec2 xz() const { return vec2(x, z); }
    vec3 yzx() const { return vec3(y, z, x); }
};

struct vec4
{
    float x, y, z, w;
    vec4(float x = 0, float y = 0, float z = 0, float w = 0):
        x(x), y(y), z(z), w(w)
    {}
};

// Deferred implementations
vec4 vec2::xyyx() const { return vec4(x, y, y, x); }
vec3 vec2::xyy() const { return vec3(x, y, y); }


// vec2 operations
vec2 operator*(const vec2 &a, float s) { return { a.x * s, a.y * s}; }
vec2 operator+(const vec2 &a, float s) { return { a.x + s, a.y + s}; }
vec2 operator-(const vec2 &a, float s) { return { a.x - s, a.y - s}; }
vec2 operator-(const vec2 &a, const vec2 &b) { return vec2(a.x-b.x, a.y-b.y); }
vec2 operator+(const vec2 &a, const vec2 &b) { return vec2(a.x+b.x, a.y+b.y); }
vec2 operator*(const vec2 &a, const vec2 &b) { return vec2(a.x*b.x, a.y*b.y); }
vec2 operator/(const vec2 &a, float s) { return vec2(a.x/s, a.y/s); }
float dot(const vec2 &a, const vec2 &b) { return a.x*b.x + a.y*b.y; }
vec2 abs(const vec2 &a) { return vec2(fabsf(a.x), fabsf(a.y)); }
vec2 &operator+=(vec2 &a, const vec2 &b) { a = a + b; return a; }
vec2 &operator+=(vec2 &a, float s) { a = a + s; return a; }
vec2 cos(const vec2 &a) { return vec2(cosf(a.x), cosf(a.y)); }
float length(const vec2 &a) { return sqrtf(a.x*a.x + a.y*a.y); }


// vec3 operations
vec3 operator*(const vec3 &a, float s) { return vec3(a.x*s, a.y*s, a.z*s); }
vec3 operator*(float s, const vec3 &a) { return a * s; }
vec3 operator+(const vec3 &a, const vec3 &b) { return vec3(a.x+b.x, a.y+b.y, a.z+b.z); }
vec3 operator-(const vec3 &a, const vec3 &b) { return vec3(a.x-b.x, a.y-b.y, a.z-b.z); }
vec3 operator-(const vec3 &a, float s) { return vec3(a.x-s, a.y-s, a.z-s); }
vec3 operator/(const vec3 &a, float s) { return vec3(a.x/s, a.y/s, a.z/s); }
vec3 &operator+=(vec3 &a, const vec3 &b) { a = a + b; return a; }
vec3 &operator+=(vec3 &a, float s) { a.x += s; a.y += s; a.z += s; return a; }
float dot(const vec3 &a, const vec3 &b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
float length(const vec3 &a) { return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z); }
vec3 normalize(const vec3 &a) { float l = length(a); return l > 0 ? a / l : vec3(); }
vec3 cross(const vec3 &a, const vec3 &b) {
    return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
vec3 sin(const vec3 &a) { return vec3(sinf(a.x), sinf(a.y), sinf(a.z)); }
vec3 cos(const vec3 &a) { return vec3(cosf(a.x), cosf(a.y), cosf(a.z)); }
vec3 round(const vec3 &a) { return vec3(roundf(a.x), roundf(a.y), roundf(a.z)); }
vec3 max(const vec3 &a, const vec3 &b) { 
    return vec3(fmaxf(a.x, b.x), fmaxf(a.y, b.y), fmaxf(a.z, b.z)); 
}

// vec4 operations
vec4 sin(const vec4 &a) { return vec4(sinf(a.x), sinf(a.y), sinf(a.z), sinf(a.w)); }
vec4 exp(const vec4 &a) { return vec4(expf(a.x), expf(a.y), expf(a.z), expf(a.w)); }
vec4 tanh(const vec4 &a) { return vec4(tanhf(a.x), tanhf(a.y), tanhf(a.z), tanhf(a.w)); }
vec4 operator+(const vec4 &a, float s) { return vec4(a.x+s, a.y+s, a.z+s, a.w+s); }
vec4 operator*(const vec4 &a, float s) { return vec4(a.x*s, a.y*s, a.z*s, a.w*s); }
vec4 operator*(float s, const vec4 &a) { return a*s; }
vec4 operator+(const vec4 &a, const vec4 &b) { return vec4(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w); }
vec4 &operator+=(vec4 &a, const vec4 &b) { a = a + b; return a; }
vec4 operator-(float s, const vec4 &a) { return vec4(s-a.x, s-a.y, s-a.z, s-a.w); }
vec4 operator/(const vec4 &a, const vec4 &b) { return vec4(a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w); }
vec4 operator/(const vec4 &a, float s) { return vec4(a.x/s, a.y/s, a.z/s, a.w/s); }


inline int clampByte(float v) {
    if (v < 0) return 0;
    if (v > 255) return 255;
    return (int)v;
}


void generateTunnel()
{
    char buf[256];
    for (int frame = 0; frame < 240; ++frame) {
        snprintf(buf, sizeof(buf), "tunnel-%03d.ppm", frame);
        const char* output_path = buf;
        FILE *f = fopen(output_path, "wb");
        
        int width = 16 * 30; // should be 60
        int height = 9 * 30;
        
        fprintf(f, "P6\n");
        fprintf(f, "%d %d\n", width, height);
        fprintf(f, "255\n");

        vec2 r = {(float)width, (float)height};
        float t = ((float)frame / 180) * 2 * M_PI;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                vec4 o;
                vec3 FC = {(float)x, (float)y, 0.0f};
                
                // Original: vec3 p,v;for(float i,z,d;i++<1e2;o+=(sin((p.z-t*.2)*vec4(3,5,9,4))+1.)/d)
                //           p=z*normalize(FC.rgb*2.-r.xyy),p+=.15,
                //           v=vec3(atan(p.x,p.y)-t*.1,length(p.xy),p.z/.2-t),
                //           z+=d=length(max(v=sin(v*7.+cos(v/.03-t)),v.yzx*.1))/1e2;
                //           o=tanh(o/1e5);
                
                vec3 p, v;
                float i = 0, z = 0, d = 0;
                
                for (; i++ < 100.0f; ) {
                    // p=z*normalize(FC.rgb*2.-r.xyy)
                    p = z * normalize(FC * 2.0f - r.xyy());
                    
                    // p+=.15
                    p += 0.15f;
                    
                    // v=vec3(atan(p.x,p.y)-t*.1,length(p.xy),p.z/.2-t)
                    v = vec3(
                        atan2f(p.x, p.y) - t * 0.1f,
                        length(p.xy()),
                        p.z / 0.2f - t
                    );
                    
                    // v=sin(v*7.+cos(v/.03-t))
                    v = sin(v * 7.0f + cos(v / 0.03f - t));
                    
                    // d=length(max(v, v.yzx*.1))/1e2
                    d = length(max(v, v.yzx() * 0.1f)) / 100.0f;
                    
                    // z+=d
                    z += d;
                    
                    // o+=(sin((p.z-t*.2)*vec4(3,5,9,4))+1.)/d (loop increment)
                    if (d > 0.0001f) {
                        o += (sin((p.z - t * 0.2f) * vec4(3, 5, 9, 4)) + 1.0f) / d;
                    }
                }
                
                // o=tanh(o/1e5);
                o = tanh(o / 100000.0f);
                
                fputc(clampByte(o.x * 255), f);
                fputc(clampByte(o.y * 255), f);
                fputc(clampByte(o.z * 255), f);
            }
        }

        fclose(f);
        printf("Generated %s\n", output_path);
    }
}

void generateShadingSphere()
{
    char buf[256];
    for (int i = 0; i < 240; ++i) {
        snprintf(buf, sizeof(buf), "output-%02d.ppm", i);
        const char* output_path = buf;
        FILE *f = fopen(output_path, "wb");
        
        int width = 16 * 60;
        int height = 9 * 60;
        
        fprintf(f, "P6\n");
        fprintf(f, "%d %d\n", width, height);
        fprintf(f, "255\n"); // max bit depth

        vec2 r = {(float)width, (float)height};
        float t = ((float)i / 240) * 2 * M_PI; // time

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                vec4 outputVector;
                vec2 FC = {(float)x, (float)y};
                // https://x.com/XorDev/status/1894123951401378051
                vec2 p = (FC*2.-r)/r.y, l, i, v = p * (l += 4. - 4. * abs(.7 - dot(p, p)));
                for(;i.y++<8.; outputVector += (sin(v.xyyx()) + 1.) * abs(v.x - v.y))v += cos(v.yx() * i.y + i + t) / i.y + .7;
                outputVector = tanh(5. * exp(l.x - 4. - p.y * vec4(-1, 1, 2, 0)) / outputVector);
                fputc(outputVector.x * 255, f);
                fputc(outputVector.y * 255, f);
                fputc(outputVector.z * 255, f);
            }
        }

        fclose(f); // close file
        printf("Generated %s\n", output_path);
    }
    return;
}

void generateAccelerator()
{
    char buf[256];
    for (int frame = 0; frame < 240; ++frame) {
        snprintf(buf, sizeof(buf), "accel-%03d.ppm", frame);
        const char* output_path = buf;
        FILE *f = fopen(output_path, "wb");
        
        int width = 16 * 60;
        int height = 9 * 60;
        
        fprintf(f, "P6\n");
        fprintf(f, "%d %d\n", width, height);
        fprintf(f, "255\n");

        vec2 r = {(float)width, (float)height};
        float t = ((float)frame / 240) * 2 * M_PI;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                vec4 o;
                vec3 FC = {(float)x, (float)y, 0.0f};
                
                // Original: for(float i,z,d,s;i++<8e1;o+=vec4(s,2,z,1)/s/d){...}
                float i = 0, z = 0, d = 0, s = 0;
                for (; i++ < 80.0f; ) {
                    // vec3 p=z*normalize(FC.rgb*2.-r.xyy),a;
                    vec3 p = z * normalize(FC * 2.0f - r.xyy());
                    vec3 a;
                    
                    // p.z+=9.;
                    p.z += 9.0f;
                    
                    // a=dot(a+=.57,p)*a*cross(a,p);
                    a += 0.57f;
                    float dotVal = dot(a, p);
                    vec3 crossVal = cross(a, p);
                    a = dotVal * a.x * crossVal.x, dotVal * a.y * crossVal.y, dotVal * a.z * crossVal.z;
                    a = vec3(dotVal * a.x * crossVal.x, 
                             dotVal * a.y * crossVal.y, 
                             dotVal * a.z * crossVal.z);
                    
                    // s=sqrt(length(a.xz-a.y-.8));
                    s = sqrtf(length(a.xz() - a.y - 0.8f));
                    
                    // for(d=2.;d++<9.;a+=sin(round(a*d)-t).yzx/d);
                    for (d = 2.0f; d++ < 9.0f; ) {
                        a += sin(round(a * d) - t).yzx() / d;
                    }
                    
                    // z+=d=length(sin(a/.1))*s/2e1;
                    d = length(sin(a / 0.1f)) * s / 20.0f;
                    z += d;
                    
                    // o+=vec4(s,2,z,1)/s/d (from loop increment)
                    if (s != 0 && d != 0) {
                        o += vec4(s, 2.0f, z, 1.0f) / s / d;
                    }
                }
                
                // o=tanh(o/4e3);
                o = tanh(o / 4000.0f);
                
                fputc(clampByte(o.x * 255), f);
                fputc(clampByte(o.y * 255), f);
                fputc(clampByte(o.z * 255), f);
            }
        }

        fclose(f);
        printf("Generated %s\n", output_path);
    }
}

int main()
{
    generateTunnel();
    return 0;
}
