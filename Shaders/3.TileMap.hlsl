
struct VertexInput
{
    float4  position : POSITION0;
    float2  uv : UV0;
    float4  color : COLOR0; //섞을색상
    float   tileMapIdx : INDICES0;
    float   tileState : STATE0;
};
// PI
struct PixelInput
{
    float4  position : SV_POSITION; //화면좌표계 포지션
    float2  uv : UV0; //매핑된 좌표
    float4  color : COLOR0; //섞을색상
    float   tileMapIdx : INDICES0;
    float   tileState : STATE0;
};

//상수버퍼 크기는 16byte배수로 만들어야한다.

cbuffer VS_WVP : register(b0) 
{
    matrix WVP;
}
cbuffer PS_LIGHT : register(b0)
{
	float2 screenPos; //스크린좌표
	float radius; //반지름크기
	float select; //남는값
	float4 lightColor; //조명 색
	float4 outColor; //외곽 색
};



//버텍스 쉐이더
//반환형  함수이름(매개변수)
// VertexInput(in) ->  VS  -> PixelInput (out)
PixelInput VS(VertexInput input)
{
    //공간변환이 있을 예정인 곳
    PixelInput output;
    output.position = mul(input.position, WVP);
	output.color = input.color;
    output.uv = input.uv;
    output.tileMapIdx = input.tileMapIdx;
    output.tileState = input.tileState;
    return output;
}

//텍스쳐 자원  (srv) 에서 연결
Texture2D Texture0 : register(t0);
SamplerState Sampler0 : register(s0);

Texture2D Texture1 : register(t1);
SamplerState Sampler1 : register(s1);

Texture2D Texture2 : register(t2);
SamplerState Sampler2 : register(s2);

Texture2D Texture3 : register(t3);
SamplerState Sampler3 : register(s3);


//픽셀쉐이더 진입 함수
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET 은 타겟이될 색깔 
{
    float4 TextureColor;
    // 매핑된 좌표로 텍스쳐 로드
   
    [branch]
    if (input.tileMapIdx == 0.0f)
    {
        TextureColor = Texture0.Sample(Sampler0, input.uv);
    }
    else if (input.tileMapIdx == 1.0f)
    {
        TextureColor = Texture1.Sample(Sampler1, input.uv);
    }
    else if (input.tileMapIdx == 2.0f)
    {
        TextureColor = Texture2.Sample(Sampler2, input.uv);
    }
    else if (input.tileMapIdx == 3.0f)
    {
        TextureColor = Texture3.Sample(Sampler3, input.uv);
    }
	//return float4(input.tileMapIdx/3.0f.xxx,1);
    
    //읽어온 그림파일의 픽셀색상을 조건문으로 비교
    [flatten]
    if (TextureColor.r == 1.0f &&
        TextureColor.g == 0.0f &&
        TextureColor.b == 1.0f)
    {
        //해당 픽셀은 사용하지않는다.
        discard;
    }

  

    
		TextureColor = TextureColor + (input.color * 2.0f - 1.0f);
    
       //벽 (개발 할때 디버깅용)   0 = none
    if (input.tileState == 1)   //wall
    {
        
        TextureColor.r += 0.5f;
        TextureColor.g = 0.0f;
        TextureColor.b = 0.0f;
        TextureColor.a = 1.0f;

    }
    if (input.tileState == 2)   //door
    {
        
        TextureColor.r = 0.0f;
        TextureColor.g = 0.5f;
        TextureColor.b = 0.0f;
        
        TextureColor.a = 1.0f;
    }
    
    if (input.tileState == 3)   //trap
    {
        
        //TextureColor.r = 0.0f;
        //TextureColor.g = 0.0f;
        //TextureColor.b = 0.5f;
        //TextureColor.a = 1.0f;
    }
    
    if (input.tileState == 4)   //stonewall
    {
        
        TextureColor.r = 0.5f;
        TextureColor.g = 0.0f;
        TextureColor.b = 0.5f;
        TextureColor.a = 1.0f;
    }
    
    if (input.tileState == 5)   //HALFBLOCK
    {
        
        TextureColor.r = 0.5f;
        TextureColor.g = 0.5f;
        TextureColor.b = 0.0f;
        TextureColor.a = 1.0f;
    }
    
	TextureColor = saturate(TextureColor);

      //조명효과
	float2 Minus = input.position.xy - screenPos;
	float dis = sqrt(Minus.x * Minus.x + Minus.y * Minus.y);
	if (select == 0.0f)
	{
		if (dis > radius)
		{
			TextureColor.rgb += (outColor.rgb * 2.0f - 1.0f);
		}
		else
		{
			TextureColor.rgb += (lightColor.rgb * 2.0f - 1.0f);
		}
	}
	else
	{
        //외각선이 0 가운데가 1
		float temp2 = pow(saturate(dis / radius), 100.0f);
		float temp = 1.0f - temp2;
        
		TextureColor.rgb =
		saturate((TextureColor.rgb + (lightColor.rgb * 2.0f - 1.0f)) * temp) +
		saturate((TextureColor.rgb + (outColor.rgb * 2.0f - 1.0f)) * temp2);
        
		//TextureColor.rgb *= temp;
	}
    
    
    
    
		return saturate(TextureColor);
}