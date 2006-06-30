<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
	<xsl:template match="/active_list">		
		<xsl:text disable-output-escaping="yes">

&lt;dialog_data&gt;
	</xsl:text>				

		<xsl:apply-templates select="node()[position()=1]" mode="attributes"/>





		<xsl:text disable-output-escaping="yes">
	&lt;values&gt;</xsl:text>				
	

		<xsl:apply-templates select="bool_cedent" mode="values"/>

		<xsl:text disable-output-escaping="yes">
	&lt;/values&gt;
		</xsl:text>				




		<xsl:text disable-output-escaping="yes">
&lt;/dialog_data&gt;
		</xsl:text>				
	</xsl:template>

	
	



	<!-- vypise atributy -->
	<xsl:template match="node()" mode="attributes">		

	<attributes>
		

		<xsl:apply-templates select="@*" mode="attributes"/>

<!--

<xsl:text disable-output-escaping="yes">
		</xsl:text>
		<attribute name="missing_values"/>
		-->
<xsl:text disable-output-escaping="yes">
		</xsl:text>
		



<xsl:text disable-output-escaping="yes">
	</xsl:text>				
	</attributes>


	</xsl:template>
	


	<!-- vypise vsechny atributy -->
	<xsl:template match="@*" mode="attributes">
	
		<xsl:text disable-output-escaping="yes">
		&lt;attribute name="</xsl:text>
	
		<xsl:value-of select="name()"/>
	
		<!-- =<xsl:value-of select="."/> -->

		<xsl:text disable-output-escaping="yes">"/&gt;</xsl:text>

	</xsl:template>






	<!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">		
		

		<xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
		<xsl:apply-templates select="@*" mode="values"/>
		<!-- vypsani literalu-->
		<xsl:text disable-output-escaping="yes">literals="</xsl:text>
		<xsl:apply-templates select="literal" mode="values" />
		<xsl:text disable-output-escaping="yes">" /&gt;</xsl:text>


	</xsl:template>



	



	
	<xsl:template match="literal" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>
		
		<xsl:text disable-output-escaping="no">(underlying attribute: </xsl:text>
		<xsl:value-of select="@underlying_attribute"/>
		<xsl:text disable-output-escaping="no">; category count: </xsl:text>
		<xsl:value-of select="@category_cnt"/>
		<xsl:text disable-output-escaping="no">; missing type: </xsl:text>
		<xsl:value-of select="@missing_type"/>
		<xsl:text disable-output-escaping="no">; coefficient type: </xsl:text>
		<xsl:value-of select="@coefficient_type"/>
		<xsl:text disable-output-escaping="no">; length: </xsl:text>
		<xsl:value-of select="@length"/>
		<xsl:text disable-output-escaping="no">; gace: </xsl:text>
		<xsl:value-of select="@gace"/>
		<xsl:text disable-output-escaping="no">; literal type: </xsl:text>
		<xsl:value-of select="@literal_type"/>
		<xsl:text disable-output-escaping="no">; equivalence class: </xsl:text>
		<xsl:value-of select="@equivalence_class"/>
		<xsl:text disable-output-escaping="no">)</xsl:text>
	</xsl:template>



	<!-- naplni hodnotu -->
	<xsl:template match="@*" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
		<xsl:value-of select="."/>

		<xsl:text disable-output-escaping="yes">" </xsl:text>

	</xsl:template>

	
	



</xsl:stylesheet>
