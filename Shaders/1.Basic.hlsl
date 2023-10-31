//hlsl ������ ��� X
struct VertexInput
{
    float4 position : POSITION0; //�ø�ƽ �뵵
    float4 color : COLOR0;
};
// PI
struct PixelInput
{
    float4 position : SV_POSITION; //ȭ����ǥ�� ������
    float4 color : COLOR0;
};

//�������: ���̴����� ���� ����� ������ �����Ë� ���ε��ϴ� ����

//������Ʈ�� ũ�� ȸ�� �̵�
cbuffer VS_WVP : register(b0) //register(b0)
{
    matrix WVP;
}
//��� ����
cbuffer VS_COLOR : register(b1)
{
    //4 ���� 4����Ʈ
    float4 color;
}
cbuffer PS_LIGHT : register(b0)
{
	float2 screenPos; //��ũ����ǥ
	float radius; //������ũ��
	float select; //���°�
	float4 lightColor; //���� ��
	float4 outColor; //�ܰ� ��
};

PixelInput VS(VertexInput input)
{
    //������ȯ�� ���� ������ ��
    PixelInput output;
    //ī�޶�,���� ���� ����� ������ȯ
    output.position = mul(input.position, WVP);
    //                             -1~ 1
    output.color = input.color + (color * 2.0f - 1.0f);
	
    //0~1
    saturate(output.color);
    
    return output;
}
//->pixel  PS   ->color
//�ȼ����̴� ���� �Լ�
float4 PS(PixelInput input) : SV_TARGET 
{
	//if (input.position.y > 200.0f)
	//{
	//	return float4(1, 0, 0, 1);
	//}
    
	float4 outputColor;
	outputColor = saturate(input.color);
    
	

      //����ȿ��
	float2 Minus = input.position.xy - screenPos;
	float dis = sqrt(Minus.x * Minus.x + Minus.y * Minus.y);
	if (select == 0.0f)
	{
		if (dis > radius)
		{
			outputColor.rgb += (outColor.rgb * 2.0f - 1.0f);
		}
		else
		{
			outputColor.rgb += (lightColor.rgb * 2.0f - 1.0f);
		}
	}
	else
	{
        //�ܰ����� 0 ����� 1
		float temp2 = pow(saturate(dis / radius), 3.0f);
		float temp = 1.0f - temp2;
        
		outputColor.rgb =
		saturate((outputColor.rgb + (lightColor.rgb * 2.0f - 1.0f)) * temp) +
		saturate((outputColor.rgb + (outColor.rgb * 2.0f - 1.0f)) * temp2);
        
		//TextureColor.rgb *= temp;
	}
    
    
	return outputColor;
}