'use strict';

const vscode = require("vscode");

/** 
 * @type {Map<string, {
 * 	default: string,
 * 	doc: string
 * }>}
 */
const PROPERTIES = new Map([
	// Java binaries
	["JAVA_SHELL", {
		default: "java",
		doc: "The path to the java binary (Java Virtual Machine)."
	}],
	["JAVAC_SHELL", {
		default: "javac",
		doc: "The path to the javac binary (Java compiler)."
	}],

	["JAVA_FLAGS", {
		default: "",
		doc: "Additionnal flags for the Java Virtual Machine."
	}],
	["JAVAC_FLAGS", {
		default: "-deprecation",
		doc: "Additionnal flags for the Java Compiler."
	}],

	// Project sources
	["MAIN_CLASS", {
		default: "Main",
		doc: "Entry point of the program."
	}],

	["PROJECT_SOURCE", {
		default: "./src",
		doc: "Relative path to sources directory."
	}],
	["PROJECT_RESOURCE", {
		default: "./resource",
		doc: "Relative path to resources directory."
	}],
	["PROJECT_OUTPUT", {
		default: "./out/src/dev",
		doc: "Relative path to sources compilation output directory."
	}],
	["PROJECT_SOURCE_TEMP", {
		default: "./tmp/project",
		doc: "Relative path to sources temporary files directory."
	}],

	// Test sources
	["MAIN_TEST_CLASS", {
		default: "Test",
		doc: "Entry point of the test program."
	}],

	["PROJECT_TEST", {
		default: "./test",
		doc: "Relative path to test sources directory."
	}],
	["PROJECT_TEST_OUTPUT", {
		default: "./out/test",
		doc: "Relative path to test compilation output directory."
	}],
	["PROJECT_TEST_TEMP", {
		default: "./tmp/test",
		doc: "Relative path to test temporary files directory."
	}]
]);

/** @type {vscode.DiagnosticCollection} */
let diagnostics;

/**
 * @param {vscode.ExtensionContext} context 
 */
function activate(context){
	diagnostics = vscode.languages.createDiagnosticCollection("juenv");

	const intellisense = vscode.languages
		.registerCompletionItemProvider("juenv", {
			provideCompletionItems(document){
				const items = [];

				for(const [identifier, prop] of PROPERTIES.entries()){
					// TODO: Maybe optimize this call to `getText()`.
					if(document.getText().includes(identifier)) continue;

					const item = new vscode.CompletionItem(identifier,
						vscode.CompletionItemKind.Variable
					);
					item.insertText=new vscode.SnippetString(
						`${item.label}=\${1:${prop.default}}`
					);
					item.documentation =
						`${prop.doc} (Default: \"${prop.default}\")`;

					items.push(item);
				}

				return items;
			}
		});


	const hover = vscode.languages.registerHoverProvider("juenv", {
		provideHover(document, position){
			const identifier = document.getText(
				document.getWordRangeAtPosition(position)
			);
			const prop = PROPERTIES.get(identifier);

			if(prop !== undefined)
				return {
					contents: [
						new vscode.MarkdownString(
							`${prop.doc}  _**Default: \"${prop.default}\"**_`
						)
					]
				};
		}
	});

	context.subscriptions.push(intellisense, hover);
};

module.exports = {
	activate
};