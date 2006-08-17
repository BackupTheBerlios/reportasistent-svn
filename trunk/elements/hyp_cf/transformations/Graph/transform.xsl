<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">

      
	
	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="GraphType">xl3DColumn</xsl:variable>
<xsl:variable name="ValuesType">rel_sum</xsl:variable>
<xsl:variable name="GraphTitle">CF Graph</xsl:variable>
<xsl:variable name="LegendShow">true</xsl:variable>
<xsl:variable name="GraphWidth">75e-2</xsl:variable>
<xsl:variable name="GraphHeight">75e-2</xsl:variable>
<xsl:variable name="ChartColor">#aa20aa</xsl:variable>

	

<msxsl:script language="JScript" implements-prefix="dedek">

	
	function normalize_value(co, cim)
	{
		return Math.round(100*(co/cim));
	}


</msxsl:script>
	


	
	
<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />
	

	
	
<!-- TEMPLATES-->	
	
	
	<xsl:template match="hyp_cf"> 


		<xsl:variable name="id_base" select="@id" />
		
		<!-- cim se bude normalizovat (normalizacni faktor)-->
		<xsl:variable name="norm_factor">
			<xsl:choose>
				<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="@sum"/></xsl:when>
				<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="@max"/></xsl:when>
				<xsl:otherwise>100</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
			
		<paragraph>
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_sdgraph">
			
			<xsl:for-each select="key('key_ti_attribute',@attributes)">
				<xsl:call-template name="categories" />  <!-- vypsani kategorii-->
			</xsl:for-each>
				
				<xsl:element name="chart">
					<xsl:attribute name="id">chart1</xsl:attribute>				
					<xsl:attribute name="title"><xsl:value-of select="key('key_ti_attribute',@attributes)/@quant" /></xsl:attribute>				
					<xsl:if test="$GraphType!='xl3DPie' and $GraphType!='xlPie'">
						<xsl:attribute name="color"><xsl:value-of select="$ChartColor" /></xsl:attribute>				
					</xsl:if>
						<xsl:for-each select="r[position()=1]/c">
							<xsl:variable name="hodnota">
								<xsl:value-of select="dedek:normalize_value(number(@val),number($norm_factor))"/>
								<xsl:if test="$ValuesType!='abs'">%</xsl:if>
							</xsl:variable>
							<value value="{$hodnota}" id="{$id_base}_val{position()}" />	
						</xsl:for-each>
				</xsl:element>			
							
			</graph>
		</paragraph>						
	
	</xsl:template>
	
	
	
	<xsl:template name="categories" >  <!-- vypise kategorie atributu-->
		
			<categories id="{@id}_cats1">
				<xsl:variable name="id_base" select="@id" />
			
				<xsl:for-each select="ti_category" >	
					<category title="{@value}" id="{$id_base}_cat{position()}" />
				</xsl:for-each>
			</categories>
			
	</xsl:template>
      




</xsl:stylesheet>
