﻿using Microsoft.VisualStudio.Designer.Interfaces;
using Microsoft.VisualStudio.TextTemplating.VSHost;
using System;
using System.CodeDom.Compiler;
using System.Collections;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.Lalr;
using System.Text.Lalr.Emitters;

namespace Contoso.VisualStudio.Generators
{
    /// <summary>
    /// LalrJS
    /// </summary>
    [ComVisible(true)]
#if VS10
    [Guid("10A7B6C6-E3DA-4bfa-A27C-8F1CEFA3DDA3")]
    [ProgId("Contoso.VisualStudio.Generators.LalrJS.10")]
#elif VS11
    [Guid("11A7B6C6-E3DA-4bfa-A27C-8F1CEFA3DDA3")]
    [ProgId("Contoso.VisualStudio.Generators.LalrJS.11")]
#endif
    [ClassInterface(ClassInterfaceType.None)]
    public class LalrJS : BaseCodeMultipleGeneratorWithSite
    {
        private Context _ctx;
        private byte[] _templateFileContents;

        /// <summary>
        /// Pres the content of the generate.
        /// </summary>
        /// <param name="inputFilePath">The input file path.</param>
        /// <param name="inputFileContents">The input file contents.</param>
        protected void PreGenerateCode(string inputFilePath, string inputFileContents)
        {
            _ctx = new Context((a, b, c, d) => GeneratorErrorCallback(false, a, b, c, d), (a, b, c, d) => GeneratorErrorCallback(true, a, b, c, d));
            Parser.Parse(_ctx, inputFilePath, inputFileContents, null);
            if (_ctx.Errors > 0)
                return;
            if (_ctx.Rules == 0)
            {
                GeneratorErrorCallback(false, 1, "Empty grammar.", 0, 0);
                return;
            }
            _ctx.Process();
            if (_ctx.Conflicts > 0)
                GeneratorErrorCallback(true, 1, string.Format("{0} parsing conflicts.", _ctx.Conflicts), 0, 0);
        }

        /// <summary>
        /// Generates the content.
        /// </summary>
        /// <param name="inputFilePath">The input file path.</param>
        /// <param name="inputFileContents">The input file contents.</param>
        /// <returns></returns>
        protected override byte[] GenerateCode(string inputFilePath, string inputFileContents)
        {
            PreGenerateCode(inputFilePath, inputFileContents);
            var newFilePath = Path.Combine(Path.GetDirectoryName(inputFilePath), Path.GetFileNameWithoutExtension(inputFilePath) + GetDefaultExtension());
            using (var s = new MemoryStream())
            {
                using (var rS = new MemoryStream(_templateFileContents))
                using (var r = new StreamReader(rS))
                using (var w = new StreamWriter(s))
                    EmitterJS.EmitTable(_ctx, r, w, false, newFilePath);
                return s.ToArray();
            }
        }

        /// <summary>
        /// Generates the content of the child.
        /// </summary>
        /// <param name="inputFilePath">The input file path.</param>
        /// <param name="inputFileContents">The input file contents.</param>
        /// <returns></returns>
        protected override byte[] GenerateChildCode(string inputFilePath, string inputFileContents)
        {
            using (var s = new MemoryStream())
                switch (Path.GetExtension(inputFilePath))
                {
                    case ".template":
                        if (!string.IsNullOrWhiteSpace(inputFileContents))
                            return (_templateFileContents = Encoding.ASCII.GetBytes(inputFileContents));
                        using (var rS = typeof(LalrJS).Assembly.GetManifestResourceStream("Contoso.Resource_.Lempar.js"))
                        using (var r = new StreamReader(rS))
                            return (_templateFileContents = Encoding.ASCII.GetBytes(r.ReadToEnd()));
                    case ".out":
                        using (var w = new StreamWriter(s))
                            Reporter.EmitOutput(_ctx, w, false);
                        return s.ToArray();
                    default: throw new InvalidOperationException();
                }
        }

        /// <summary>
        /// Gets the default extension.
        /// </summary>
        /// <returns></returns>
        public override string GetDefaultExtension()
        {
            var fileExtension = GetCodeDomProvider().FileExtension;
            if (!string.IsNullOrEmpty(fileExtension) && fileExtension[0] != '.')
                fileExtension = "." + fileExtension;
            return fileExtension;
        }

        /// <summary>
        /// Gets the enumerator.
        /// </summary>
        /// <returns></returns>
        public override IEnumerator GetEnumerator() { return new[] { "*.template", "*.out" }.GetEnumerator(); }

        private CodeDomProvider _codeDomProvider;
        /// <summary>
        /// Gets the code DOM provider.
        /// </summary>
        /// <returns></returns>
        protected CodeDomProvider GetCodeDomProvider()
        {
            if (_codeDomProvider == null)
            {
                var service = (IVSMDCodeDomProvider)GetService(new Guid("{73E59688-C7C4-4a85-AF64-A538754784C5}")); //: CodeDomInterfaceGuid
                if (service != null)
                    _codeDomProvider = (CodeDomProvider)service.CodeDomProvider;
            }
            return _codeDomProvider;
        }
    }
}
