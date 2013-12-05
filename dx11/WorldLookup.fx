//@author: vux
//@help: standard constant shader
//@tags: color
//@credits: 

Texture2D colorTexture <string uiname="Texture";>;
Texture2D<float3> worldTexture <string uiname="World";>;

SamplerState g_samLinear : IMMUTABLE
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};

SamplerState g_samPoint : IMMUTABLE
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Clamp;
    AddressV = Clamp;
};
 
cbuffer cbPerDraw : register( b0 )
{
	float4x4 tVP : VIEWPROJECTION;
};


cbuffer cbPerObj : register( b1 )
{
	float4x4 tW : WORLD;
	float Alpha <float uimin=0.0; float uimax=1.0;> = 1; 
	float4 cAmb <bool color=true;String uiname="Color";> = { 1.0f,1.0f,1.0f,1.0f };
	float4x4 tColor <string uiname="Color Transform";>;
};

struct VS_IN
{
	float4 PosO : POSITION;
	float4 TexCd : TEXCOORD0;

};

struct vs2ps
{
    float4 PosWVP: SV_POSITION;
    float4 TexCd: TEXCOORD0;
	bool Discard : TEXCOORD1;
};

vs2ps VS(VS_IN input)
{
	vs2ps Out = (vs2ps)0;
	
	float4 PosO;
	PosO.w = 1.0f;
	PosO.xyz = worldTexture[input.TexCd.xy];
    Out.PosWVP  = mul(PosO,mul(tW,tVP));
    Out.TexCd = input.TexCd;
	Out.Discard = length(PosO.xyz) < 1e-7;
    return Out;
}




float4 PS(vs2ps In): SV_Target
{
	if (In.Discard) {
		discard;
	}
    float4 col = colorTexture[In.TexCd.xy] * cAmb;
	col.a *= Alpha;
    return col;
}





technique10 Constant
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetPixelShader( CompileShader( ps_4_0, PS() ) );
	}
}




