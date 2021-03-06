<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
	<xsl:template match="/active_list">		
		<xsl:text disable-output-escaping="yes">

&lt;dialog_data&gt;
		</xsl:text>				

		<xsl:apply-templates select="hyp_4ft[position()=1]" mode="attributes"/>





		<xsl:text disable-output-escaping="yes">
	&lt;values&gt;</xsl:text>				
	

		<xsl:apply-templates select="hyp_4ft" mode="values"/>

		<xsl:text disable-output-escaping="yes">
	&lt;/values&gt;
		</xsl:text>				




		<xsl:text disable-output-escaping="yes">
&lt;/dialog_data&gt;
		</xsl:text>				
	</xsl:template>

	
	



	<!-- vypise atributy -->
	<xsl:template match="node()" mode="attributes">		
		
		<xsl:text disable-output-escaping="yes">
	&lt;attributes&gt;</xsl:text>				

		<xsl:apply-templates select="@*" mode="attributes"/>

		<xsl:text disable-output-escaping="yes">
	&lt;/attributes&gt;
		</xsl:text>				

	</xsl:template>
	


	<!-- vypise vsechny atributy -->
	<xsl:template match="@*" mode="attributes">
	
		<xsl:text disable-output-escaping="yes">
		&lt;attribute name="</xsl:text>
	
		<xsl:value-of select="name()"/>
	
		<!-- =<xsl:value-of select="."/> -->

		<xsl:text disable-output-escaping="yes">"/&gt;</xsl:text>

    	<xsl:apply-templates select="@*"/>
	</xsl:template>






	<!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">		
		

		<xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
		<xsl:apply-templates select="@*" mode="values"/>
		<xsl:text disable-output-escaping="yes">/&gt;</xsl:text>


	</xsl:template>



	<!-- naplni hodnotu -->
	<xsl:template match="@*" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
		<xsl:value-of select="."/>

		<xsl:text disable-output-escaping="yes">" </xsl:text>

    	<xsl:apply-templates select="@*"/>
	</xsl:template>

	
	
	<!-- naplni hodnotu cedentu-->
	<xsl:template match="@antecedent | @succedent | @condition" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
    	<xsl:apply-templates select="id(.)" mode="values"/>

		<xsl:text disable-output-escaping="yes">" </xsl:text>

    	<xsl:apply-templates select="@*"/>
	</xsl:template>
	

	<!-- literaly -> cedent -->
	<xsl:template match="ti_cedent" mode="values">		
    	<xsl:apply-templates select="ti_literal" mode="values"/>
	</xsl:template>
	

	<!-- preformatuje literal -->
	<xsl:template match="ti_literal" mode="values">		
		
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no"> &amp; </xsl:text>
		</xsl:if>

		
		<xsl:value-of select="@quant"/>
		<xsl:text disable-output-escaping="yes">(</xsl:text>
		<xsl:value-of select="@value"/>
		<xsl:text disable-output-escaping="yes">)</xsl:text>
	</xsl:template>
	






</xsl:stylesheet>
