using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SkyNet.SkyrimOnline.Game
{
    [Flags]
    public enum ID_TESWeather : uint
    {
        DefaultWeather = 0x0000015E,
        SovngardeDark = 0x0010FEF8,
        RiftenOvercastFog = 0x0010FE7E,
        EditorCloudPreview = 0x0010E3D4,
        SkyrimClear_A = 0x0010E1F2,
        SkyrimCloudy_A = 0x0010E1F1,
        SkyrimClearSN_A = 0x0010E1F0,
        SkyrimCloudySN_A = 0x0010E1EF,
        SkyrimClearTU_A = 0x0010E1EE,
        SkyrimCloudyTU_A = 0x0010E1ED,
        SkyrimClearFF_A = 0x0010E1EC,
        SkyrimCloudyFF_A = 0x0010E1EB,
        SkyrimClearRE_A = 0x0010E1EA,
        SkyrimCloudyRE_A = 0x0010E1E9,
        SkyrimClearCO_A = 0x0010E1E8,
        SkyrimCloudyCO_A = 0x0010E1E7,
        SkyrimClearMA_A = 0x0010E1E6,
        SkyrimCloudyMA_A = 0x0010E1E5,
        SkyrimClearVT_A = 0x0010E1E4,
        SkyrimCloudyVT_A = 0x0010E1E3,
        FXWthrInvertWindowsWinterhold = 0x0010DA13,
        SovngardeClear = 0x0010D9EC,
        FXSkyrimStormBlowingGrass = 0x0010C32F,
        SkyrimCloudyVT = 0x0010A7A8,
        SkyrimFogVT = 0x0010A7A7,
        SkyrimOvercastRainVT = 0x0010A7A6,
        SkyrimClearVT = 0x0010A7A5,
        SkyrimCloudySN = 0x0010A245,
        SkyrimClearSN = 0x0010A244,
        SkyrimCloudyTU = 0x0010A243,
        SkyrimOvercastRainTU = 0x0010A242,
        SkyrimStormRainTU = 0x0010A241,
        SkyrimClearTU = 0x0010A240,
        SkyrimCloudyFF = 0x0010A23F,
        SkyrimFogFF = 0x0010A23E,
        SkyrimOvercastRainFF = 0x0010A23D,
        SkyrimStormRainFF = 0x0010A23C,
        SkyrimClearFF = 0x0010A23B,
        SkyrimCloudyRE = 0x0010A23A,
        SkyrimFogRE = 0x0010A239,
        SkyrimOvercastRainRE = 0x0010A238,
        SkyrimClearRE = 0x0010A237,
        SkyrimCloudyCO = 0x0010A236,
        SkyrimFogCO = 0x0010A235,
        SkyrimClearCO = 0x0010A234,
        SkyrimCloudyMA = 0x0010A233,
        SkyrimFogMA = 0x0010A232,
        SkyrimOvercastRainMA = 0x0010A231,
        SkyrimClearMA = 0x0010A230,
        KarthspireRedoubtFog = 0x00106635,
        SkyrimDA02Weather = 0x00105F40,
        SolitudeBluePalaceFog = 0x00105945,
        SolitudeBluePalaceFogNMARE = 0x00105944,
        SolitudeBluePalaceFogFEAR = 0x00105943,
        SolitudeBluePalaceFogARENA = 0x00105942,
        BloatedMansGrottoFog = 0x00105941,
        SkuldafnCloudy = 0x00104AB4,
        SkyrimMQ206weather = 0x0010199F,
        FXWthrInvertLightMarkarth = 0x00101910,
        FXWthrInvertWindowsWindhelm2 = 0x000ECC96,
        HelgenAttackWeather = 0x000D9329,
        FXWthrInvertLightsSolitude = 0x0005ED7A,
        FXWthrInvertLightsWhiterun = 0x0008282A,
        FXWthrInvertWindowsWhiterun = 0x0008277A,
        FXMagicStormRain = 0x000D4886,
        SkyrimOvercastWar = 0x000D299E,
        SkyrimStormSnow = 0x000C8221,
        SkyrimStormRain = 0x000C8220,
        SkyrimOvercastRain = 0x000C821F,
        SkyrimFog = 0x000C821E,
        FXWthrSunlightWhite = 0x00075491,
        FXWthrSunlight = 0x0007548F,
        BlackreachWeather = 0x00048C14,
        FXWthrInvertWindowsWindhelm = 0x000AEE84,
        WorldMapWeather = 0x000A6858,
        SovngardeFog = 0x000923FD,
        FXWthrInvertDayNighWarm = 0x000777CF,
        FXWthrCaveBluePaleLight = 0x00075DE5,
        FXWthrCaveBlueSkylight = 0x0006ED5B,
        FXWthrInvertDayNight = 0x0006ED5A,
        SkyrimOvercastSnow = 0x0004D7FB,
        TESTCloudyRain = 0x0002E7AB,
        SkyrimCloudy = 0x00012F89,
        SkyrimClear = 0x0000081A
    };
    public class WeatherManager
    {
        internal static readonly Dictionary<ID_TESWeather, string> WeatherCore = new Dictionary<ID_TESWeather, string>() 
        #region Weather Defines
        {
            { ID_TESWeather.DefaultWeather, "Default" },
            {ID_TESWeather.SovngardeDark, "SovngardeDark"},
			{ID_TESWeather.RiftenOvercastFog, "RiftenOvercastFog"},
			{ID_TESWeather.EditorCloudPreview, "EditorCloudPreview"},
			{ID_TESWeather.SkyrimClear_A, "SkyrimClear_A"},
			{ID_TESWeather.SkyrimCloudy_A, "SkyrimCloudy_A"},
			/*ID_TESWeather.SkyrimClearSN_A,
			ID_TESWeather.SkyrimCloudySN_A,
			ID_TESWeather.SkyrimClearTU_A,
			ID_TESWeather.SkyrimCloudyTU_A,
			ID_TESWeather.SkyrimClearFF_A,
			ID_TESWeather.SkyrimCloudyFF_A,
			ID_TESWeather.SkyrimClearRE_A,
			ID_TESWeather.SkyrimCloudyRE_A,
			ID_TESWeather.SkyrimClearCO_A,
			ID_TESWeather.SkyrimCloudyCO_A,
			ID_TESWeather.SkyrimClearMA_A,
			ID_TESWeather.SkyrimCloudyMA_A,
			ID_TESWeather.SkyrimClearVT_A,
			ID_TESWeather.SkyrimCloudyVT_A,
			ID_TESWeather.FXWthrInvertWindowsWinterhold,*/ // 20
			{ID_TESWeather.SovngardeClear, "SovngardeClear"},
			{ID_TESWeather.FXSkyrimStormBlowingGrass, "FXSkyrimStormBlowingGrass"},
			{ID_TESWeather.SkyrimCloudyVT, "SkyrimCloudyVT"},
			{ID_TESWeather.SkyrimFogVT, "SkyrimFogVT"},
			{ID_TESWeather.SkyrimOvercastRainVT, "SkyrimOvercastRainVT"}, // 25
			/*ID_TESWeather.SkyrimClearVT,
			ID_TESWeather.SkyrimCloudySN,
			ID_TESWeather.SkyrimClearSN,*/   // 28
			{ID_TESWeather.SkyrimCloudyTU, "SkyrimCloudyTU"},
			{ID_TESWeather.SkyrimOvercastRainTU, "SkyrimOvercastRainTU"}, // 30
			{ID_TESWeather.SkyrimStormRainTU, "SkyrimStormRainTU"},
			{ID_TESWeather.SkyrimClearTU, "SkyrimClearTU"},
			//ID_TESWeather.SkyrimCloudyFF,
			{ID_TESWeather.SkyrimFogFF, "SkyrimFogFF"},
			/*ID_TESWeather.SkyrimOvercastRainFF,
			ID_TESWeather.SkyrimStormRainFF,*/
			{ID_TESWeather.SkyrimClearFF, "SkyrimClearFF"},
			/*ID_TESWeather.SkyrimCloudyRE,
			ID_TESWeather.SkyrimFogRE,
			ID_TESWeather.SkyrimOvercastRainRE, // 40
			ID_TESWeather.SkyrimClearRE,*/
			/*ID_TESWeather.SkyrimCloudyCO,
			ID_TESWeather.SkyrimFogCO,
			ID_TESWeather.SkyrimClearCO,
			ID_TESWeather.SkyrimCloudyMA,
			ID_TESWeather.SkyrimFogMA,
			ID_TESWeather.SkyrimOvercastRainMA,
			ID_TESWeather.SkyrimClearMA,*/
			{ID_TESWeather.KarthspireRedoubtFog, "KarthspireRedoubtFog"},
			{ID_TESWeather.SkyrimDA02Weather, "SkyrimDA02Weather"}, // 50
			{ID_TESWeather.SolitudeBluePalaceFog, "SolitudeBluePalaceFog"},
			{ID_TESWeather.SolitudeBluePalaceFogNMARE, "SolitudeBluePalaceFogNMARE"},
			{ID_TESWeather.SolitudeBluePalaceFogFEAR, "SolitudeBluePalaceFogFEAR"},
			{ID_TESWeather.SolitudeBluePalaceFogARENA, "SolitudeBluePalaceFogARENA"},
			{ID_TESWeather.BloatedMansGrottoFog, "BloatedMansGrottoFog"},// 55
			{ID_TESWeather.SkuldafnCloudy, "SkuldafnCloudy"},
			{ID_TESWeather.SkyrimMQ206weather, "SkyrimMQ206weather"},
			//ID_TESWeather.FXWthrInvertLightMarkarth,
			//ID_TESWeather.FXWthrInvertWindowsWindhelm2,
			//ID_TESWeather.HelgenAttackWeather, // 60
			//ID_TESWeather.FXWthrInvertLightsSolitude,
			//ID_TESWeather.FXWthrInvertLightsWhiterun,
			//ID_TESWeather.FXWthrInvertWindowsWhiterun,
			{ID_TESWeather.FXMagicStormRain, "FXMagicStormRain"},
			{ID_TESWeather.SkyrimOvercastWar, "SkyrimOvercastWar"},
			{ID_TESWeather.SkyrimStormSnow, "SkyrimStormSnow"},
			{ID_TESWeather.SkyrimStormRain, "SkyrimStormRain"},
			{ID_TESWeather.SkyrimOvercastRain, "SkyrimOvercastRain"},
			{ID_TESWeather.SkyrimFog, "SkyrimFog"},
			//ID_TESWeather.FXWthrSunlightWhite,
			{ID_TESWeather.FXWthrSunlight, "FXWthrSunlight"},
			{ID_TESWeather.BlackreachWeather, "BlackreachWeather"},
			//ID_TESWeather.FXWthrInvertWindowsWindhelm,
			//ID_TESWeather.WorldMapWeather,
			{ID_TESWeather.SovngardeFog, "SovngardeFog"},
			//ID_TESWeather.FXWthrInvertDayNighWarm,
			//ID_TESWeather.FXWthrCaveBluePaleLight,
			{ID_TESWeather.FXWthrCaveBlueSkylight, "FXWthrCaveBlueSkylight"},
			//ID_TESWeather.FXWthrInvertDayNight,
			{ID_TESWeather.SkyrimOvercastSnow, "SkyrimOvercastSnow"},
			//ID_TESWeather.TESTCloudyRain,
			//ID_TESWeather.SkyrimCloudy,
			{ID_TESWeather.SkyrimClear, "SkyrimClear"}
        };
#endregion
        public uint Current { get; set; }
        public ID_TESWeather CurrentBase
        {
            get { return (ID_TESWeather)Current; }
            set { Current = (uint)value; }
        }
        public WeatherManager()
        {
            Current = 0x0000081A;
        }
        internal void Update(float Elapsed)
        {

        }
    }
}
