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
using System;
using System.Runtime.CompilerServices;
using System.Resources;

namespace Contoso.Practices.ConsoleCommand
{
    /// <summary>
    /// CommandAttribute
    /// </summary>
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = true)]
    public sealed class CommandAttribute : Attribute
    {
        private string _description;
        private string _example;
        private string _usageDescription;
        private string _usageSummary;

        /// <summary>
        /// Initializes a new instance of the <see cref="CommandAttribute"/> class.
        /// </summary>
        /// <param name="commandName">Name of the command.</param>
        /// <param name="description">The description.</param>
        public CommandAttribute(string commandName, string description)
        {
            CommandName = commandName;
            Description = description;
            MinArgs = 0;
            MaxArgs = int.MaxValue;
        }
        /// <summary>
        /// Initializes a new instance of the <see cref="CommandAttribute"/> class.
        /// </summary>
        /// <param name="resourceType">Type of the resource.</param>
        /// <param name="commandName">Name of the command.</param>
        /// <param name="descriptionResourceName">Name of the description resource.</param>
        public CommandAttribute(Type resourceType, string commandName, string descriptionResourceName)
        {
            ResourceType = resourceType;
            CommandName = commandName;
            DescriptionResourceName = descriptionResourceName;
            MinArgs = 0;
            MaxArgs = int.MaxValue;
        }

        /// <summary>
        /// Gets or sets the name of the alt.
        /// </summary>
        /// <value>
        /// The name of the alt.
        /// </value>
        public string AltName { get; set; }
        /// <summary>
        /// Gets the name of the command.
        /// </summary>
        /// <value>
        /// The name of the command.
        /// </value>
        public string CommandName { get; private set; }
        /// <summary>
        /// Gets the description.
        /// </summary>
        public string Description
        {
            get { return ResourceManagerEx.GetStringOrDefault(ResourceType, DescriptionResourceName, _description); }
            private set { _description = value; }
        }
        /// <summary>
        /// Gets the name of the description resource.
        /// </summary>
        /// <value>
        /// The name of the description resource.
        /// </value>
        public string DescriptionResourceName { get; private set; }
        /// <summary>
        /// Gets or sets the max args.
        /// </summary>
        /// <value>
        /// The max args.
        /// </value>
        public int MaxArgs { get; set; }
        /// <summary>
        /// Gets or sets the min args.
        /// </summary>
        /// <value>
        /// The min args.
        /// </value>
        public int MinArgs { get; set; }
        /// <summary>
        /// Gets the type of the resource.
        /// </summary>
        /// <value>
        /// The type of the resource.
        /// </value>
        public Type ResourceType { get; private set; }
        /// <summary>
        /// Gets or sets the usage description.
        /// </summary>
        /// <value>
        /// The usage description.
        /// </value>
        public string UsageDescription
        {
            get { return ResourceManagerEx.GetStringOrDefault(ResourceType, UsageDescriptionResourceName, _usageDescription); }
            set { _usageDescription = value; }
        }
        /// <summary>
        /// Gets or sets the name of the usage description resource.
        /// </summary>
        /// <value>
        /// The name of the usage description resource.
        /// </value>
        public string UsageDescriptionResourceName { get; set; }
        /// <summary>
        /// Gets or sets the usage example.
        /// </summary>
        /// <value>
        /// The usage example.
        /// </value>
        public string UsageExample
        {
            get { return ResourceManagerEx.GetStringOrDefault(ResourceType, UsageExampleResourceName, _example); }
            set { _example = value; }
        }
        /// <summary>
        /// Gets or sets the name of the usage example resource.
        /// </summary>
        /// <value>
        /// The name of the usage example resource.
        /// </value>
        public string UsageExampleResourceName { get; set; }
        /// <summary>
        /// Gets or sets the usage summary.
        /// </summary>
        /// <value>
        /// The usage summary.
        /// </value>
        public string UsageSummary
        {
            get { return ResourceManagerEx.GetStringOrDefault(ResourceType, UsageSummaryResourceName, _usageSummary); }
            set { _usageSummary = value; }
        }
        /// <summary>
        /// Gets or sets the name of the usage summary resource.
        /// </summary>
        /// <value>
        /// The name of the usage summary resource.
        /// </value>
        public string UsageSummaryResourceName { get; set; }
    }
}

