﻿#region License
/*
The MIT License

Copyright (c) 2008 Sky Morey

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#endregion
using System.Runtime;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;

namespace System.Net
{
    /// <summary>
    /// TdsException
    /// </summary>
    public class TdsException : ExternalException
    {
        private int _tdsCode;

        /// <summary>
        /// Initializes a new instance of the <see cref="TdsException"/> class.
        /// </summary>
        [TargetedPatchingOptOut("Performance critical to inline this type of method across NGen image boundaries")]
        public TdsException() { }
        /// <summary>
        /// Initializes a new instance of the <see cref="TdsException"/> class.
        /// </summary>
        /// <param name="message">The message.</param>
        [TargetedPatchingOptOut("Performance critical to inline this type of method across NGen image boundaries")]
        public TdsException(string message)
            : base(message) { }
        /// <summary>
        /// Initializes a new instance of the <see cref="TdsException"/> class.
        /// </summary>
        /// <param name="tdsCode">The TDS code.</param>
        /// <param name="message">The message.</param>
        [TargetedPatchingOptOut("Performance critical to inline this type of method across NGen image boundaries")]
        public TdsException(int tdsCode, string message)
            : base(message)
        {
            _tdsCode = tdsCode;
        }
        /// <summary>
        /// Initializes a new instance of the <see cref="TdsException"/> class.
        /// </summary>
        /// <param name="info">The object that holds the serialized object data.</param>
        /// <param name="context">The contextual information about the source or destination.</param>
        /// <exception cref="T:System.ArgumentNullException">
        ///   <paramref name="info"/> is null. </exception>
        protected TdsException(SerializationInfo info, StreamingContext context)
            : base(info, context)
        {
            _tdsCode = info.GetInt32("_tdsCode");
        }
        /// <summary>
        /// Initializes a new instance of the <see cref="TdsException"/> class.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="innerException">The inner exception.</param>
        [TargetedPatchingOptOut("Performance critical to inline this type of method across NGen image boundaries")]
        public TdsException(string message, Exception innerException)
            : base(message, innerException) { }
        /// <summary>
        /// Initializes a new instance of the <see cref="TdsException"/> class.
        /// </summary>
        /// <param name="tdsCode">The TDS code.</param>
        /// <param name="message">The message.</param>
        /// <param name="innerException">The inner exception.</param>
        [TargetedPatchingOptOut("Performance critical to inline this type of method across NGen image boundaries")]
        public TdsException(int tdsCode, string message, Exception innerException)
            : base(message, innerException)
        {
            _tdsCode = tdsCode;
        }
    }

}
