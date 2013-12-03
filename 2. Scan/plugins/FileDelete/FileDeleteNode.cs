#region usings
using System;
using System.IO;
using System.ComponentModel.Composition;

using VVVV.PluginInterfaces.V1;
using VVVV.PluginInterfaces.V2;
using VVVV.Utils.VColor;
using VVVV.Utils.VMath;

using VVVV.Core.Logging;
#endregion usings

namespace VVVV.Nodes
{
	#region PluginInfo
	[PluginInfo(Name = "Delete", Category = "File", Help = "Delete a file from disk", Tags = "", AutoEvaluate = true)]
	#endregion PluginInfo
	public class FileDeleteNode : IPluginEvaluate
	{
		#region fields & pins
		[Input("Filename", StringType = StringType.Filename)]
		public ISpread<string> FInput;
		
		[Input("Delete", IsBang = true)]
		ISpread<bool> FDelete;

		[Output("Status")]
		public ISpread<string> FStatus;

		[Import()]
		public ILogger FLogger;
		#endregion fields & pins

		//called when data for any output pin is requested
		public void Evaluate(int SpreadMax)
		{
			FStatus.SliceCount = SpreadMax;

			for (int i = 0; i < SpreadMax; i++)
			{
				if (FDelete[i]) 
				{
					try
					{
						File.Delete(FInput[i]);
						FStatus[i] = "OK";
					}
					catch(Exception e)
					{
						FStatus[i] = e.Message;
					}
				}
			}
		}
	}
}
